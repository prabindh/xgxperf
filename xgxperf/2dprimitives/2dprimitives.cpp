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
 
 //This library allows profiling 2D primitive drawing - 2 ellipse and 
 // surface blits in this case.

#include "2dprimitives.h"   

//Definition of QWidget subclass
class ellipseClass: public QWidget
{
public:
  ellipseClass(QWidget* parent, QRectF inRect):
    QWidget(parent)
    {    
      //Store the test data locally
      currRect = inRect;
    }
protected:  
  void paintEvent(QPaintEvent *event)
  {
    QPainter painter;
    QPainterPath tempPath, tempPath1;
       
    painter.begin(this);

    red = (red++ > 250) ? 0 : red;
    tempPath.addEllipse(currRect);
    //inverted ellipse
    //Using red component for changing height
    tempPath1.addEllipse(currRect.x(), currRect.y(), red, currRect.width());       
    painter.fillRect(currRect, QColor(red, 122,122));
    painter.fillPath(tempPath, QColor(122, red,122));
    painter.fillPath(tempPath1, QColor(122, 122,red) );    
        
    painter.end();
  }
private:
  QRectF currRect;
  int red;  
}; 

 
TEMPLATE_APP_NAME::TEMPLATE_APP_NAME(QWidget* parent, QRectF inSceneRect,   
    QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene,data) 
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
}
// Deprecated 
QString TEMPLATE_APP_NAME::GetAppName(){return QString("");};
// Deprecated 
QIcon TEMPLATE_APP_NAME::GetAppIcon(){return QIcon();};  
int TEMPLATE_APP_NAME::GetSwitchingTime()
{
  return (1000/m_widgetTestInStruct->rate_screen_refresh_fps); 
};

void TEMPLATE_APP_NAME::Init()
{
  ellipseClassPtr = new ellipseClass(0, QRect(0,0,480,640));
  ellipseClassPtr->resize(480,640);
  proxyWorkItemList << m_scene->addWidget(ellipseClassPtr);   
}

void TEMPLATE_APP_NAME::Process()
{
  ellipseClassPtr->update();
  //Indicate that the processing is complete
  SetProcessCallComplete();   
}
