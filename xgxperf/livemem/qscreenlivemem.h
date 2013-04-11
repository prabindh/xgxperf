/****************************************************************************
**
** 
** LiveMem QScreen driver for Qt Embedded
**
** This Screen Driver for Qt/Embedded allows systems that do not have a 
** natively supported output interface (ex, with no FrameBuffer), to use a
** file as a screen surface. The file can be read to see the output of 
** rendering operations.
**
** https://gforge.ti.com/gf/project/gleslayer/
** 
** prabu@ti.com
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

#ifndef QSCREENLIVEMEM_H
#define QSCREENLIVEMEM_H

#include <QtGui/qscreen_qws.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_QWS_LIVEMEM

class QLiveMemScreenPrivate;

class Q_GUI_EXPORT QLiveMemScreen : public QScreen
{
public:
    explicit QLiveMemScreen(int display_id);
    virtual ~QLiveMemScreen();

    virtual bool initDevice();
    virtual bool connect(const QString &displaySpec);

    virtual bool useOffscreen();

    virtual void disconnect();
    virtual void shutdownDevice();
    virtual void setMode(int,int,int);
    virtual void save();
    virtual void restore();
    virtual void blank(bool on);
    virtual void set(unsigned int,unsigned int,unsigned int,unsigned int);
    virtual uchar * cache(int);
    virtual void uncache(uchar *);
    virtual int sharedRamSize(void *);

protected:

    void deleteEntry(uchar *);

    bool canaccel;
    int dataoffset;
    int cacheStart;

    static void clearCache(QScreen *instance, int);

private:

    void delete_entry(int);
    void insert_entry(int,int,int);
    void setupOffScreen();
    void setPixelFormat();

    QLiveMemScreenPrivate *d_ptr;
};

#endif // QT_NO_QWS_LIVEMEM

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSCREENLIVEMEM_H
