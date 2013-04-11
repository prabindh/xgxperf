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

#include <qscreendriverplugin_qws.h>
#include <qscreenlivemem.h>
#include <qstringlist.h>

QT_BEGIN_NAMESPACE

class QScreenLiveMemPlugin : public QScreenDriverPlugin
{
public:
    QScreenLiveMemPlugin();

    QStringList keys() const;
    QScreen *create(const QString&, int displayId);
};

QScreenLiveMemPlugin::QScreenLiveMemPlugin()
    : QScreenDriverPlugin()
{
}

QStringList QScreenLiveMemPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("LiveMem");
    return list;
}

QScreen* QScreenLiveMemPlugin::create(const QString& driver, int displayId)
{
    if (driver.toLower() == QLatin1String("livemem"))
        return new QLiveMemScreen(displayId);

    return 0;
}

Q_EXPORT_PLUGIN2(qscreenlivemem, QScreenLiveMemPlugin)

QT_END_NAMESPACE
