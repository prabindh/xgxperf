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


#include "browserlib.h"

//Main class
BrowserApp::BrowserApp(QWidget* parent, 
          QRectF inSceneRect, QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene, data)
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
  completedPage = 0;          

   connect(&m_htmlpage, SIGNAL(loadFinished(bool)), this, SLOT(webpageLoadComplete(bool)));
   connect(&m_htmlpage, SIGNAL(loadStarted()), this, SLOT(webpageLoadStart()));
   
   currUrlId = 0;   
  
}

int BrowserApp::Na2dperfCreateTestWidget(TestTargetParamsStruct* pwidget_test)
{
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;

  //covering grid  
  workItemList << m_scene->addRect(
                    0,0,m_scene->sceneRect().width(),
                      m_scene->sceneRect().height());     
  //update size of widgets
  unitwidth = m_scene->sceneRect().width();
  unitheight = m_scene->sceneRect().height();  
  if(pwidget_test->size_widget)
    unitwidth=unitheight=pwidget_test->size_widget;
  //Create parent and add to view
  tempWidget = new QLabel(0);
    tempWidget->resize(unitwidth, unitheight);
    if(pwidget_test->transparent)        
      tempWidget->setWindowOpacity(0.6);
    if(pwidget_test->effects)
      tempWidget->setGraphicsEffect(effect);
    //Move to position
    rectItem = m_scene->addWidget(tempWidget);
    rectItem->moveBy(10, 10);        
    //Add to item list for later maintenance    
    workItemList << rectItem;    
    
    m_scene->addWidget(tempWidget);
                               
  return 0;
}

void BrowserApp::Init()
{
  //Widget tests 
  Na2dperfCreateTestWidget(m_widgetTestInStruct);  
}

void BrowserApp::Process()
{
  currUrlId ++;
  currUrlId &= 3;
  //Open new page
  urlList[0] = QString("file:///na2dperf/na2dperf.html");  
  urlList[1] = QString("file:///na2dperf/qtdocs.htm");
  urlList[2] = QString("file:///na2dperf/beagleboard.htm"); 
  
  //Create the page frame and load first page
  qDebug() << "Creating browser";

  m_htmlpage.setViewportSize(QSize(unitwidth, unitheight));
  
  SetProcessCallWaiting();//Indicate that this is an async call
  m_htmlpage.mainFrame()->load(QUrl(urlList[currUrlId]));
  
}

void BrowserApp::webpageLoadStart()
{
  qDebug() << "load start called";
}

void BrowserApp::webpageLoadComplete(bool completed)
{
  if(completed)
  { 
    completedPage = 1;    
    qDebug() << "load completed no errors";
  }
  else
      qDebug() << "load called but with errors";
      
    QPixmap pixmap(QSize(unitwidth, unitheight));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    m_htmlpage.mainFrame()->render(&painter);
    painter.end();
    ((QLabel*)tempWidget)->setPixmap(pixmap);
    
    //Indicate that the processing is complete
    SetProcessCallComplete();
}
