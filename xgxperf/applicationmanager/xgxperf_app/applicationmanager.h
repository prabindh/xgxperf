/*****************************************************************************
 * applicationmanager.h
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

#ifndef _APPLICATIONMANAGER_H
#define _APPLICATIONMANAGER_H
/**
 * Contains the Top level application manager structures. The application manager
 * is responsible for ::\n
 * 1. Loading new applications \n
 * 2. Maintaining state of running applications \n
 * 3. Maintaining the time and calling application process hooks \n
 * 4. Managing the top level icon panels depending on the applications loaded \n 
 * 5. Profiling the screen switch times, and the Process call times and display  
 * them overlaid on the screen (enabled only in DEBUG build)
 *   
 * To add a new application to the framework, do the following steps: \n
 * 1. Derive new class from ApplicationBase and implement functionality  \n  
 * 2. Make the ApplicationManager aware of that class by adding it in \n 
 *  loadApplications() of ApplicationManager implementation in  \n 
 *   applicationmanager.cpp \n                                                 
 * 3. Create icon for the app and add it to sitara.qrc \n  
 * 
 *  In the future, this registration can be made automatic using a configure
 *  script that is loaded at start, or similar.\n      
 *
 *  /sa ApplicationManager, ApplicationBase       
 */
#include <QtGui>
#include <QtWidgets/QGraphicsEffect>
#include <QtWidgets/QGraphicsView>
 #include <QTimer> 

#include "../common/applicationbase.h"
class ApplicationManager: public QGraphicsView
{
    Q_OBJECT
public:
    ApplicationManager(QWidget *parent = 0, 
          QList<int> testParamList=QList<int>(), 
          QString targetAppName=0,
          QString inCookie=0);    
private:
    void setupScene();   
    bool loadTargetApp(QString name);               
public slots:
    void TimerAnimate();
public:    
    QGraphicsScene m_scene;        
    QTimer* pTimer1;               
    int currStateID;
    QList<QGraphicsItem *> workItemList;         
    QList<ApplicationBase *> appList;
private:                           
    int currScreenWidth;    
    int currScreenHeight;
    void WriteOutputData();
    QString m_currAppName;
};

#define AM_ICON_HEIGHT 48
#define AM_ICON_WIDTH 115

#define AM_APP_NAME "Texas Instruments XgxPerf"

#endif //_APPLICATIONMANAGER_H
