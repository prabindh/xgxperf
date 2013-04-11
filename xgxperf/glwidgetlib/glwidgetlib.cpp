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

#include "glwidgetlib.h"

//Definition of QGLWidget subclass
class GLNa2dperfWidget: public QGLWidget
{
public:
  GLNa2dperfWidget(QGLFormat format, QWidget* parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent){}
protected:  
  void paintEvent(QPaintEvent *event)
  {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawEllipse(QRectF(0,0, 60, 60));
    painter.drawText(QRect(10,10, 100, 100), Qt::AlignCenter, "OpenGL Perf");
       
    painter.end();
  }
}; 
//Main Class
GLWidgetApp::GLWidgetApp(QWidget* parent, 
          QRectF inSceneRect, QGraphicsScene *scene, void* data): 
            ApplicationBase(parent, inSceneRect,scene, data)
{
  //Store the test data locally
  m_widgetTestInStruct = (TestTargetParamsStruct*)data;   
}
QString GLWidgetApp::GetAppName(){return QString("GLNa2DPERF");};
QIcon GLWidgetApp::GetAppIcon(){return QIcon(":/images/GLna2dperf.png");};
int GLWidgetApp::GetSwitchingTime()
{
  return (1000/m_widgetTestInStruct->rate_screen_refresh_fps);
};

int GLWidgetApp::Na2dperfCreateTestWidget(TestTargetParamsStruct* pwidget_test)
{
  //Create widgets
  QPen currPen(Qt::black, 4.0);  
  int unitwidth;
  int unitheight;
  QGraphicsProxyWidget *rectItem;
  QWidget* tempWidget;
  QGraphicsTextItem *pText;  
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
  effect->setBlurRadius(10);

  //covering grid  
  workItemList << m_scene->addRect(
                    0,0,m_scene->sceneRect().width(),
                      m_scene->sceneRect().height());
  //update size of widgets
  unitwidth = m_scene->sceneRect().width();
  unitheight = m_scene->sceneRect().height();
  //update size of widgets
  if(pwidget_test->size_widget)
    unitwidth=unitheight=pwidget_test->size_widget;                      

  //Create all items iteratively   
  for(int i=0,xoffset=0,yoffset=0;i < pwidget_test->num_widgets; i++)
  {  
    //Calculate offset of new item
    xoffset = yoffset = i*10;
    //Add item
    tempWidget = new GLNa2dperfWidget(QGLFormat(QGL::SampleBuffers), 0);        
    tempWidget->resize(unitwidth, unitheight);
    //set transparency
    if(pwidget_test->transparent)        
      tempWidget->setWindowOpacity(0.6);
    if(pwidget_test->effects)
      tempWidget->setGraphicsEffect(effect);
    //Move to position
    rectItem = m_scene->addWidget(tempWidget);
    rectItem->moveBy(xoffset, yoffset);        
    pText = m_scene->addText(QString("%1 %2 %3 %4 %5").arg(xoffset).
          arg(yoffset).arg(unitwidth).arg(unitheight).arg((long)tempWidget));
    pText->moveBy(xoffset, yoffset);      
    //Add to item list for later maintenance    
    workItemList << rectItem;
    workItemList << pText;    
  }   
  return 0;
}

void GLWidgetApp::Init()
{
  //Widget tests 
  Na2dperfCreateTestWidget(m_widgetTestInStruct);  
}

void GLWidgetApp::Process()
{
  for(int i=0; i < workItemList.count();i ++)  
    workItemList[i]->moveBy(off,off);
  if(off>0)off=-5; else off=5;
}

