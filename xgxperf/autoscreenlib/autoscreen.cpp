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

#include "autoscreen.h"

AutoscreenApp::AutoscreenApp(QWidget* parent, QRectF inSceneRect, 
    QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene,data)
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
}
QString AutoscreenApp::GetAppName(){return QString("Autoscreen");};
QIcon AutoscreenApp::GetAppIcon(){return QIcon(":/images/autoscreen.png");};
int AutoscreenApp::GetSwitchingTime()
{
  return (1000/m_widgetTestInStruct->rate_screen_refresh_fps);
};

void AutoscreenApp::Init()
{
  m_scene->addText("Automotive Screen Example - Xgxperf");
  pRotor2 = m_scene->addPixmap(QPixmap(":/images/tacho.PNG"));
  pRotor2->moveBy(0,0);
  workItemList << pRotor2;
  pSpeedVal1 = m_scene->addText("Liquid Full");
  pSpeedVal1->moveBy(80,305);  
  workItemList << pSpeedVal1;
  workItemList << m_scene->addRect(75,295,150,30);  

  pSpeedVal = m_scene->addText("Temperature Normal");
  pSpeedVal->moveBy(80,360);                
  workItemList << pSpeedVal;
  workItemList << m_scene->addRect(75,350,150,30);  

  pGearVal = m_scene->addText("Neutral");
  pGearVal->moveBy(80,400+10);                
  workItemList << pGearVal;
  workItemList << m_scene->addRect(75,400,200,30);  

  pTyreVal = m_scene->addText("Tyre status : Ok");
  pTyreVal->moveBy(80,440+10);                
  workItemList << pTyreVal;
  workItemList << m_scene->addRect(75,440,200,30);  

  QPen currPen(Qt::yellow, 10.0);
  pNeedle = m_scene->addLine(100,440,150,340,currPen);
  workItemList << pNeedle;

  speedcounter = 0;
}

void AutoscreenApp::Process()
{
   speedcounter += 10;
	speedcounter %= 200;

   if(currTimerCount & 1)    
    {    
      pSpeedVal1->setDefaultTextColor(Qt::red);
      pSpeedVal1->setPlainText("Liquid Empty");
      pSpeedVal->setDefaultTextColor(Qt::red);
      pSpeedVal->setPlainText("Temperature High");      
      pGearVal->setPlainText("Park | Reverse | Neutral | 2D");
      pTyreVal->setPlainText("Tyre status: Rear Tyre Puncture");	      
    }
    else    
    {    
      pSpeedVal1->setDefaultTextColor(Qt::black);
      pSpeedVal1->setPlainText("Liquid Full");      
      pSpeedVal->setDefaultTextColor(Qt::black);
      pSpeedVal->setPlainText("Temperature Normal");      
      pGearVal->setPlainText("Reverse | Neutral | 2D");      
      pTyreVal->setPlainText("Tyre status: Ok");	      
    }
	pNeedle->setLine(395,380,300+speedcounter,280);
    currTimerCount ++;
    
  //Indicate that the processing is complete
  SetProcessCallComplete();    
}
