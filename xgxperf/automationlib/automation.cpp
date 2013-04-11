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

#include "automation.h"


AutomationApp::AutomationApp(QWidget* parent, QRectF inSceneRect, 
    QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene,data)
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;  
    currTimerCount = 0;  
	needle1Angle = 0;
	needle2Angle = 30;
	needle3Angle = 60;
	fan1Angle = 0;
}
QString AutomationApp::GetAppName(){return QString("Automation");};
QIcon AutomationApp::GetAppIcon(){return QIcon(":/images/automationicon.PNG");};
int AutomationApp::GetSwitchingTime()
{
  return (1000/m_widgetTestInStruct->rate_screen_refresh_fps);
};

void AutomationApp::Init()
{
  QPen currPen(Qt::black, 4.0);
  QPen arrowPen(Qt::red, 1.0);    
  QGraphicsPixmapItem *tempItem;	
  QFont monitorFont("Cronyx-Helvetica", 22,10);

  //covering grid  
  workItemList << m_scene->addRect(0,0,480 ,640 );

  //Title
  QGraphicsTextItem* tempTextItem = m_scene->addText("Automation HMI");
  tempTextItem->setFont(monitorFont);
  tempTextItem->moveBy(100,0);  
  workItemList << tempTextItem;                
  
  //Bottles
  pBottle1 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle1->setPos(600,200);
  m_scene->addItem(pBottle1);
  workItemList << pBottle1;
  pBottle2 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle2->setPos(620,250);
  m_scene->addItem(pBottle2);
  workItemList << pBottle2;
  pBottle3 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle3->setPos(640,250);
  m_scene->addItem(pBottle3);
  workItemList << pBottle3;
  pBottle4 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle4->setPos(660,250);
  m_scene->addItem(pBottle4);
  workItemList << pBottle4;
  pBottle5 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle5->setPos(680,250);
  m_scene->addItem(pBottle5);
  workItemList << pBottle5;
  pBottle6 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle6->setPos(720,250);
  m_scene->addItem(pBottle6);
  workItemList << pBottle6;
  pBottle7 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle7->setPos(760,250);
  m_scene->addItem(pBottle7);
  workItemList << pBottle7;
  pBottle8 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(10,30));
  pBottle8->setPos(800,250);
  m_scene->addItem(pBottle8);
  workItemList << pBottle8;



  //Bottom most row
  pBoiler = new QGraphicsSvgNativeItem(":/images/svg/boiler.svg");
  pBoiler->setPos(10,450);
  m_scene->addItem(pBoiler);
  workItemList << pBoiler;

  pBoilerPipe1 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(15,90));
  pBoilerPipe1->setPos(55,440);
  pBoilerPipe1->setRotation(90);
  m_scene->addItem(pBoilerPipe1);
  workItemList << pBoilerPipe1;

  pArrow1 = new QGraphicsSvgNativeItem(":/images/svg/arrow.svg");
  pArrow1->setPos(30,440);
  pArrow1->setRotation(90);
  m_scene->addItem(pArrow1);
  workItemList << pArrow1;

  pBoilerPipe3 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(15,280));
  pBoilerPipe3->setPos(150,460);
  pBoilerPipe3->setRotation(180);
  m_scene->addItem(pBoilerPipe3);
  workItemList << pBoilerPipe3;

  pBoilerPipe7 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(10,90));
  pBoilerPipe7->setPos(130,460);
  pBoilerPipe7->setRotation(270);
  m_scene->addItem(pBoilerPipe7);
  workItemList << pBoilerPipe7;

  pBoilerPipe8 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(10,60));
  pBoilerPipe8->setPos(200,400);
  m_scene->addItem(pBoilerPipe8);
  workItemList << pBoilerPipe8;


  pFan = new QGraphicsSvgNativeItem(":/images/svg/fan.svg");
  pFan->setPos(160,485);
  pFan->setTransformOriginPoint(33,33);
  m_scene->addItem(pFan);
  workItemList << pFan;

  pBoiler1 = new QGraphicsSvgNativeItem(":/images/svg/boiler.svg");
  pBoiler1->setPos(250,450);
  m_scene->addItem(pBoiler1);
  workItemList << pBoiler1;

  pBoilerPipe4 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(15,250));
  pBoilerPipe4->setPos(305,460);
  pBoilerPipe4->setRotation(180);
  m_scene->addItem(pBoilerPipe4);
  workItemList << pBoilerPipe4;

  pBoilerPipe9 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(10,60));
  pBoilerPipe9->setPos(380,400);
  m_scene->addItem(pBoilerPipe9);
  workItemList << pBoilerPipe9;

  //Second from bottom
  pChamber = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg");
  pChamber->setPos(10,200);
  m_scene->addItem(pChamber);
  workItemList << pChamber;

  pLBend2 = new QGraphicsSvgNativeItem(":/images/svg/l_bend.svg");
  pLBend2->setPos(40,180);
  m_scene->addItem(pLBend2);
  workItemList << pLBend2;

  pBoilerPipe2 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg", QSize(15,800));
  pBoilerPipe2->setPos(50,195);
  pBoilerPipe2->setRotation(270);
  m_scene->addItem(pBoilerPipe2);
  workItemList << pBoilerPipe2;

  pValve1 = new QGraphicsSvgNativeItem(":/images/svg/valve2.svg");
  pValve1->setPos(120,170);
  m_scene->addItem(pValve1);
  workItemList << pValve1;

  pValveText1 = new InfoBoxClass(0,QRectF(100,220,20,20),"1.1");
  m_scene->addItem(pValveText1);
  workItemList << pValveText1;


  pMeter1 = new QGraphicsSvgNativeItem(":/images/svg/meter.svg");
  pMeter1->setPos(25,300);
  m_scene->addItem(pMeter1);
  workItemList << pMeter1;
  pMeter1Needle1 = new QGraphicsSvgNativeItem(":/images/svg/needle.svg");
  pMeter1Needle1->setPos(20+10,300);
  pMeter1Needle1->setTransformOriginPoint(10,30);
  m_scene->addItem(pMeter1Needle1);
  workItemList << pMeter1Needle1;

  pChamber1 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg");
  pChamber1->setPos(180,200);
  m_scene->addItem(pChamber1);
  workItemList << pChamber1;

  pBoilerPipe5 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg");
  pBoilerPipe5->setPos(220,180);
  m_scene->addItem(pBoilerPipe5);
  workItemList << pBoilerPipe5;

  pValve2 = new QGraphicsSvgNativeItem(":/images/svg/valve2.svg");
  pValve2->setPos(280,170);
  m_scene->addItem(pValve2);
  workItemList << pValve2;

  pValveText2 = new InfoBoxClass(0,QRectF(320,220,20,20),"21");
  m_scene->addItem(pValveText2);
  workItemList << pValveText2;

  pMeter2 = new QGraphicsSvgNativeItem(":/images/svg/meter.svg");
  pMeter2->setPos(180+15,300);
  m_scene->addItem(pMeter2);
  workItemList << pMeter2;
  pMeter1Needle2 = new QGraphicsSvgNativeItem(":/images/svg/needle.svg");
  pMeter1Needle2->setPos(190+10,300);
  pMeter1Needle2->setTransformOriginPoint(10,30);
  pMeter1Needle2->setRotation(30);
  m_scene->addItem(pMeter1Needle2);
  workItemList << pMeter1Needle2;

  pChamber2 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg");
  pChamber2->setPos(360,200);
  m_scene->addItem(pChamber2);
  workItemList << pChamber2;

  pBoilerPipe6 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg");
  pBoilerPipe6->setPos(400,180);
  m_scene->addItem(pBoilerPipe6);
  workItemList << pBoilerPipe6;

  pMeter3 = new QGraphicsSvgNativeItem(":/images/svg/meter.svg");
  pMeter3->setPos(360+15,300);
  m_scene->addItem(pMeter3);
  workItemList << pMeter3;
  pMeter1Needle3 = new QGraphicsSvgNativeItem(":/images/svg/needle.svg");
  pMeter1Needle3->setPos(370+10,300);
  pMeter1Needle3->setTransformOriginPoint(10,30); //Item coordinates
  pMeter1Needle3->setRotation(60);
  m_scene->addItem(pMeter1Needle3);
  workItemList << pMeter1Needle3;


  pChamber3 = new QGraphicsSvgNativeItem(":/images/svg/boiler1.svg", QSize(100,400));
  pChamber3->setPos(500,200);
  m_scene->addItem(pChamber3);
  workItemList << pChamber3;

  pBoilerPipe10 = new QGraphicsSvgNativeItem(":/images/svg/pipe.svg");
  pBoilerPipe10->setPos(540,180);
  m_scene->addItem(pBoilerPipe10);
  workItemList << pBoilerPipe10;

  pMeter4 = new QGraphicsSvgNativeItem(":/images/svg/meter.svg");
  pMeter4->setPos(510+15,300);
  m_scene->addItem(pMeter4);
  workItemList << pMeter4;
  pMeter1Needle4 = new QGraphicsSvgNativeItem(":/images/svg/needle.svg");
  pMeter1Needle4->setPos(525+10,300);
  pMeter1Needle4->setTransformOriginPoint(10,30); //Item coordinates
  pMeter1Needle4->setRotation(60);
  m_scene->addItem(pMeter1Needle4);
  workItemList << pMeter1Needle4;

  //Third row
  pHistoWidget = new HistoWidget(80, NULL);
  pHistoWidget->resize(80,50);
  QGraphicsProxyWidget* tempItem1 = m_scene->addWidget(pHistoWidget);
  tempItem1->setPos(30,100);
  proxyWorkItemList << tempItem1;

  pHistoWidget1 = new HistoWidget(80, NULL);
  pHistoWidget1->resize(80,50);
  tempItem1 = m_scene->addWidget(pHistoWidget1);
  tempItem1->setPos(130,100);
  proxyWorkItemList << tempItem1;

  pHistoWidget2 = new HistoWidget(80, NULL);
  pHistoWidget2->resize(80,50);
  tempItem1 = m_scene->addWidget(pHistoWidget2);
  tempItem1->setPos(230,100);
  proxyWorkItemList << tempItem1;

  pHistoWidget3 = new HistoWidget(80, NULL);
  pHistoWidget3->resize(80,50);
  tempItem1 = m_scene->addWidget(pHistoWidget3);
  tempItem1->setPos(330,100);
  proxyWorkItemList << tempItem1;
}

void AutomationApp::Process()
{
  currTimerCount ++;

  if(needle1Angle > 120) needle1Angle = 0;
  if(needle2Angle > 120) needle2Angle = 0;
  if(needle3Angle > 120) needle3Angle = 0;
  if(fan1Angle > 360) fan1Angle = 0;
  if(arrowPos > 20) arrowPos = 0;
  if(bottlePos > 100) bottlePos = 0;
  if(bottleYPos > 50) bottleYPos = 0;

  pMeter1Needle1->setRotation(needle1Angle++);
  pMeter1Needle2->setRotation(needle2Angle++);
  pMeter1Needle3->setRotation(needle3Angle++);
  pFan->setRotation(fan1Angle);
  pArrow1->setPos(30+(arrowPos++),440);
  fan1Angle += 10;

  pHistoWidget->setVal((float)needle1Angle*sin(needle1Angle)/4);
  pHistoWidget->update();

  pHistoWidget1->setVal((float)needle2Angle*sin(needle2Angle)/4);
  pHistoWidget1->update();

  pHistoWidget2->setVal((float)needle3Angle*sin(needle3Angle)/4);
  pHistoWidget2->update();

  pHistoWidget3->setVal((float)needle3Angle*tan(needle3Angle)/4);
  pHistoWidget3->update();

  bottlePos += 10;
  bottleYPos += 2;
  pBottle1->setPos(600, 200+bottleYPos);
  pBottle2->setPos(620+bottlePos, 250);
  pBottle3->setPos(640+bottlePos, 250);
  pBottle4->setPos(660+bottlePos, 250);
  pBottle5->setPos(680+bottlePos, 250);
  pBottle6->setPos(720+bottlePos, 250);
  pBottle7->setPos(760+bottlePos, 250);
  pBottle8->setPos(800+bottlePos, 250);

process_complete:
  QPen currPen(Qt::black, 4.0);
  //Indicate that the processing is complete
  SetProcessCallComplete();    
}
