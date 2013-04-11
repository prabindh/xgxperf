/*****************************************************************************
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

#include "ecgmonitor.h"   

 
EcgMonitorApp::EcgMonitorApp(QWidget* parent, QRectF inSceneRect,   
    QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene,data) 
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
	currTimerCount = 0; 
}
QString EcgMonitorApp::GetAppName(){return QString("EcgMonitor");};
QIcon EcgMonitorApp::GetAppIcon(){return QIcon(":/images/ecgmonitor.png");};  
int EcgMonitorApp::GetSwitchingTime()
{
  return (1000/m_widgetTestInStruct->rate_screen_refresh_fps); 
};

void EcgMonitorApp::Init()
{
  QGraphicsProxyWidget *rectItem;

  int unitwidth = 480;
  int unitheight = 640;   

    pMonitorWidget = new Na2dperfWidget(0);
    pMonitorWidget->resize(unitwidth, unitheight);        
    rectItem = m_scene->addWidget(pMonitorWidget);
    //Add to item list for later maintenance    
    workItemList << rectItem;

}

void EcgMonitorApp::Process()
{
 currTimerCount += 5;
 currTimerCount %= 100;
 pMonitorWidget->setOffset(currTimerCount);   
 pMonitorWidget->update();
  //Indicate that the processing is complete
  SetProcessCallComplete();   
}
