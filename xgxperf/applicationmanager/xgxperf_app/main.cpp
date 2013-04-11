/*****************************************************************************
 * main.cpp
 *
 * More details at
 *   
 * http://www.gforge.ti.com/gf/project/gleslayer  
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *   
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *   
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "applicationmanager.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#define USAGE_STRING "Usage: xgxperf_app (Application Manager for Qt applications) \n\
cookie<0,1,2..>\n<numWdgts=3,.>\n<fx=0,1>\n<transparency=0,1>\n<texture=0,1,2>\n<fontsize=8,16..>\n<fps=1,..>\n<prebuiltID=0,1,2,3,10\n<wdgtsize=100,256,512><numFrames=100,200..>\n<appstring>\n For example,\n\
 ./xgxperf_app [-qws] 123 3 0 0 0 0 10 99 512 100 \"vslib\" \n\
Default invocation runs the Automation demo for ~100 seconds.\n\
"

int main(int argc, char **argv)
{
    int i;
    QList<int> paramList;
    QApplication app(argc, argv);
    QString targetAppName, inCookie;
    
    if(argc < 10) 
    {
      qDebug() << USAGE_STRING;
      inCookie = QString("123");
      paramList << 3 << 0 << 0 << 0 << 0 << 10 << 99 << 512 << 1000;
      targetAppName = QString("automation");
    }
    else
    {
      inCookie = QString(argv[1]);
      for(i=2;i<argc-1;i++){paramList << atol(argv[i]);/*qDebug() << paramList[i-2]*/;}
      targetAppName = QString(argv[i]);
    }
    qDebug() << targetAppName;
     
    ApplicationManager applicationManager(0,paramList, targetAppName, inCookie);
    QDesktopWidget *wdgt = app.desktop();        
    applicationManager.setFixedSize(
	//480,640);
	wdgt->screenGeometry().width(), 
          wdgt->screenGeometry().height());
    applicationManager.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, AM_APP_NAME));    
    applicationManager.show();
    return app.exec();
}
