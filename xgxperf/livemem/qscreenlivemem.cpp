/****************************************************************************
** 
** LiveMem QScreen driver for Qt Embedded
**
** This Screen Driver for Qt/Embedded allows systems that do not have a 
** natively supported output interface (ex, with no FrameBuffer), to use a
** file as a screen surface. The file can be read to see the output of 
** rendering operations.
**
** Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
**
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   Redistributions of source code must retain the above copyright
**   notice, this list of conditions and the following disclaimer.
**   
**   Redistributions in binary form must reproduce the above copyright
**   notice, this list of conditions and the following disclaimer in the
**   documentation and/or other materials provided with the
**   distribution.
**   
**   Neither the name of Texas Instruments Incorporated nor the names of
**   its contributors may be used to endorse or promote products derived
**   from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
**
***************************************************************************/

#include "qscreenlivemem.h"

#ifndef QT_NO_QWS_LIVEMEM
#include "qwsdisplay_qws.h"
#include "qpixmap.h"
#include <private/qwssignalhandler_p.h>
#include <private/qcore_unix_p.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/kd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <signal.h>

#include "qwindowsystem_qws.h"

//Driver Configuration parameters. This sucks.
//TODO: Move to a saner way of passing parameters to driver.
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define BIT_DEPTH 16
#define LIVEMEM_DEVICE_NAME "/opt/livemem/livemem.bin"
#define SCREEN_PHYSICAL_WIDTH_MM 60 //Physical Width of Screen - For calculating DPI
#define SCREEN_PHYSICAL_HEIGHT_MM 70 

QT_BEGIN_NAMESPACE

extern int qws_client_id;

/**
 * No need to do disable console blinking for LIVEMEM
**/

class QLiveMemScreenPrivate : public QObject
{
public:
    QLiveMemScreenPrivate();
    ~QLiveMemScreenPrivate();

    int fd;
#ifdef QT_QWS_DEPTH_GENERIC
    bool doGenericColors;
#endif
    QString displaySpec;
};

QLiveMemScreenPrivate::QLiveMemScreenPrivate()
    : fd(-1)
#ifdef QT_QWS_DEPTH_GENERIC
      ,doGenericColors(false)
#endif
{
    QWSSignalHandler::instance()->addObject(this);
}

QLiveMemScreenPrivate::~QLiveMemScreenPrivate()
{
}


QLiveMemScreen::QLiveMemScreen(int display_id)
    : QScreen(display_id, CustomClass), d_ptr(new QLiveMemScreenPrivate)
{
    canaccel=false;
    clearCacheFunc = &clearCache;
#ifdef QT_QWS_CLIENTBLIT
    setSupportsBlitInClients(true);
#endif
}

QLiveMemScreen::~QLiveMemScreen()
{
}

bool QLiveMemScreen::connect(const QString &displaySpec)
{
    d_ptr->displaySpec = displaySpec;

    const QStringList args = displaySpec.split(QLatin1Char(':'));

#ifdef QT_QWS_DEPTH_GENERIC
    if (args.contains(QLatin1String("genericcolors")))
        d_ptr->doGenericColors = true;
#endif

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
#ifndef QT_QWS_FRAMEBUFFER_LITTLE_ENDIAN
    if (args.contains(QLatin1String("littleendian")))
#endif
        QScreen::setFrameBufferLittleEndian(true);
#endif
    
    //Open the file device
    QString dev = QLatin1String(LIVEMEM_DEVICE_NAME);


    if (access(dev.toLatin1().constData(), F_OK) == -1)
    {
	fprintf(stderr,"Livemem device file does not exist - creating ...\n");
        d_ptr->fd = QT_OPEN(dev.toLatin1().constData(), O_RDWR | O_CREAT);
	//Write dummy data, as the device has to be of sufficient size !!!
	for(int dummyD=0;dummyD<SCREEN_HEIGHT*SCREEN_WIDTH*BIT_DEPTH/8;dummyD++) write(d_ptr->fd,&dummyD,1);
	QT_CLOSE(d_ptr->fd);
	if (d_ptr->fd == -1) {
            fprintf(stderr,"File %s does not exist. Additionally, the create operation failed\n", LIVEMEM_DEVICE_NAME);
        return false;
        }
	d_ptr->fd=-1;
    }

    if (access(dev.toLatin1().constData(), R_OK|W_OK) == 0)
        d_ptr->fd = QT_OPEN(dev.toLatin1().constData(), O_RDWR);
    if (d_ptr->fd == -1) {
        fprintf(stderr,"Cannot open %s\n", LIVEMEM_DEVICE_NAME);
        return false;
    }

    grayscale = 0;
    d = BIT_DEPTH;
    lstep = SCREEN_WIDTH*2; //line length
    //TODO: take care of rotation for lstep

    //Passing dummy value
    setPixelFormat();

    /* Figure out the size of the screen in bytes */
    size = SCREEN_HEIGHT * lstep;

    mapsize = size;

    //Change below to suit the screen
    dw = w = SCREEN_WIDTH;
    dh = h = SCREEN_HEIGHT;
    physWidth = SCREEN_PHYSICAL_WIDTH_MM; //width of screen in millimetre
    physHeight = SCREEN_PHYSICAL_HEIGHT_MM; //height of screen in millimetre

    data = (unsigned char *)-1;
    if (d_ptr->fd != -1)
        data = (unsigned char *)mmap(0, mapsize, PROT_READ | PROT_WRITE,
                                     MAP_SHARED, d_ptr->fd, 0);

    if ((long)data == -1) {
        if (QApplication::type() == QApplication::GuiServer) {
            fprintf(stderr,"Fatal error: Unable to mmap Livemem device\n");
            return false;
        }
        data = 0;
    }

    canaccel = useOffscreen();
    if(canaccel)
        setupOffScreen();

    fprintf(stderr,"%s successful, data=%x\n",__FUNCTION__, data);
    return true;
}

void QLiveMemScreen::disconnect()
{
    if (data)
        munmap((char*)data,mapsize);
    close(d_ptr->fd);
}

bool QLiveMemScreen::initDevice()
{
    grayscale = 0;

#ifndef QT_NO_QWS_CURSOR
    QScreenCursor::initSoftwareCursor();
#endif

    return true;
}
void QLiveMemScreen::setPixelFormat()
{
    QImage::Format format = QImage::Format_Invalid;

    if(BIT_DEPTH == 16)
	    format = QImage::Format_RGB16;
    QScreen::setPixelFormat(format);
}
//Save it for the last
void QLiveMemScreen::delete_entry(int pos)
{
    if (pos > *entryp || pos < 0) {
        qWarning("Attempt to delete odd pos! %d %d", pos, *entryp);
        return;
    }

    QPoolEntry *qpe = &entries[pos];
    if (qpe->start <= *lowest) {
        // Lowest goes up again
        *lowest = entries[pos-1].start;
    }

    (*entryp)--;
    if (pos == *entryp)
        return;

    int size = (*entryp)-pos;
    memmove(&entries[pos], &entries[pos+1], size*sizeof(QPoolEntry));
}

void QLiveMemScreen::insert_entry(int pos, int start, int end)
{
    if (pos > *entryp) {
        qWarning("Attempt to insert odd pos! %d %d",pos,*entryp);
        return;
    }

    if (start < (int)*lowest) {
        *lowest = start;
    }

    if (pos == *entryp) {
        entries[pos].start = start;
        entries[pos].end = end;
        entries[pos].clientId = qws_client_id;
        (*entryp)++;
        return;
    }

    int size=(*entryp)-pos;
    memmove(&entries[pos+1],&entries[pos],size*sizeof(QPoolEntry));
    entries[pos].start=start;
    entries[pos].end=end;
    entries[pos].clientId=qws_client_id;
    (*entryp)++;
}

uchar * QLiveMemScreen::cache(int amount)
{
	fprintf(stderr,"%s called, amount=%x\n", __FUNCTION__, amount);
        return 0;
}

void QLiveMemScreen::uncache(uchar * c)
{
	fprintf(stderr,"%s called with %c\n",__FUNCTION__,*c);
}

void QLiveMemScreen::deleteEntry(uchar * c)
{
	fprintf(stderr,"%s called with %c\n",__FUNCTION__,*c);
}

void QLiveMemScreen::clearCache(QScreen *instance, int clientId)
{
	fprintf(stderr,"%s called with %x %d",__FUNCTION__, instance, clientId);	
}


void QLiveMemScreen::setupOffScreen()
{
}

void QLiveMemScreen::shutdownDevice()
{
}

void QLiveMemScreen::set(unsigned int i,unsigned int r,unsigned int g,unsigned int b)
{
	fprintf(stderr,"%s called with %d %d %d %d\n",__FUNCTION__,i,r,g,b);
}

void QLiveMemScreen::setMode(int nw,int nh,int nd)
{
	fprintf(stderr,"%s called with %d %d %d\n",__FUNCTION__,nw,nh,nd);
}

void QLiveMemScreen::save()
{
    // nothing to do.
}


void QLiveMemScreen::restore()
{
}

int QLiveMemScreen::sharedRamSize(void * end)
{
    fprintf(stderr,"%s called with %x\n",__FUNCTION__, end);	
    return 0;
}

void QLiveMemScreen::blank(bool on)
{
    fprintf(stderr,"%s called with %x\n",__FUNCTION__, on);	
}



bool QLiveMemScreen::useOffscreen()
{
        return false;
}

QT_END_NAMESPACE

#endif // QT_NO_QWS_LINUXFB
