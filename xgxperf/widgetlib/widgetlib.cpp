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


#include "widgetlib.h"


#define TEST_STRING "<p>Lorem ipsum dolor sit amet consectetuer auctor quam \
tincidunt nibh consectetuer. Elit nec tincidunt sodales pede quam semper \
pellentesque a Nunc sociis. Malesuada vel quis vel congue Vivamus dui Curabitur \
lacus orci vitae. Justo feugiat volutpat metus nibh convallis tortor leo \
Vivamus Morbi quis. Gravida enim Nam molestie consectetuer ipsum.</p>        \
<p>Integer eget nonummy Vestibulum nec Curabitur quis eget nibh et \
sollicitudin. Quis pellentesque ipsum dui in id commodo urna Phasellus \
Curabitur dolor. Et lobortis sit facilisi massa interdum lorem dapibus \
Curabitur accumsan hac. Tellus volutpat velit condimentum ac dis Morbi \
et tempus vel Curabitur. Fringilla porttitor risus est Fusce quis Vestibulum \
 eleifend libero convallis cursus. Hendrerit.</p> \
<p>Sed consectetuer porttitor et tincidunt Curabitur volutpat orci Aenean \
pellentesque a. Nulla Phasellus tellus eu tincidunt consequat sociis augue \
 at Vivamus augue. Ligula nec pretium interdum pretium pretium Nulla tempus \
 orci condimentum massa. Tristique tempor pede pharetra laoreet ac adipiscing \
 commodo vel pellentesque sed. Amet a In Sed adipiscing id libero malesuada \
 sem lobortis nascetur. Dui rhoncus adipiscing dictumst condimentum nibh \
 consequat.</p> <p>Felis metus nulla tortor aliquam pretium a id Morbi diam \
 penatibus. Accumsan urna ut Duis lacinia laoreet et ligula lorem nibh \
 pharetra. Id nulla justo ligula id odio elit at commodo Maecenas dolor. \
 Id quis elit nulla tempus magna habitant non tempus magna nec. Pellentesque \
 rutrum libero sed interdum nunc sit nibh sodales tellus et. </p>"


//Definition of QWidget subclass
class Na2dperfWidget: public QWidget
{
public:
  Na2dperfWidget(QWidget* parent, int type_texture):
    QWidget(parent)
    {    
      //Store the test data locally
      m_type_texture = type_texture;
    }
protected:  
  void paintEvent(QPaintEvent *event)
  {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    if(m_type_texture == 1)
      painter.drawPixmap(0,0,QPixmap(":/images/sunset.PNG"));
    else if(m_type_texture == 2)
      painter.drawPixmap(0,0,QPixmap(":/images/tiger.svg"));      
    painter.drawEllipse(QRectF(200,0, 60, 60));
    painter.drawText(QRect(10,10, 100, 100), Qt::AlignCenter, 
                QString("QWidget Perf %1").arg(x()));            
    painter.end();
  }
private:
  int m_type_texture;
}; 

//Main class
WidgetApp::WidgetApp(QWidget* parent, 
          QRectF inSceneRect, QGraphicsScene *scene, void* data): 
ApplicationBase(parent, inSceneRect,scene, data)
{
    //Store the test data locally
    m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
}

int WidgetApp::Na2dperfCreateTestWidget(TestTargetParamsStruct* pwidget_test)
{
  //Create widgets
  QPen currPen(Qt::black, 4.0);  
  int unitwidth;
  int unitheight = m_scene->sceneRect().height();
  QGraphicsProxyWidget *rectItem, *rectItemText;
  QWidget* tempWidget;
  QTextEdit *tempText;
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
  if(pwidget_test->size_widget)
    unitwidth=unitheight=pwidget_test->size_widget;                      
  //Create all items iteratively   
  for(int i=0,xoffset=0,yoffset=0;i < pwidget_test->num_widgets; i++)
  { 
    qDebug() << "numwidgets = " << pwidget_test->num_widgets; 
    //Calculate offset of new item
    xoffset = yoffset = i*10;
    
    //Create item
    tempWidget = new Na2dperfWidget(0, pwidget_test->type_texture);
    tempWidget->resize(unitwidth, unitheight);        
    //set transparency
    if(pwidget_test->transparent)        
      tempWidget->setWindowOpacity(0.6);
    if(pwidget_test->effects)
      tempWidget->setGraphicsEffect(effect);
    //Add text
    if(pwidget_test->size_font)
    {
      tempText = new QTextEdit(QString(TEST_STRING), 0);
      tempText->setLineWrapMode(QTextEdit::WidgetWidth);
      rectItemText = m_scene->addWidget(tempText);
      rectItemText->moveBy(xoffset, yoffset);
      workItemList << rectItemText;        
    }
    //Move to position
    rectItem = m_scene->addWidget(tempWidget);
    rectItem->moveBy(xoffset, yoffset);        
    pText = m_scene->addText(QString("%1 %2 %3 %4").arg(xoffset).
                  arg(yoffset).arg(unitwidth).arg(unitheight));
    pText->moveBy(xoffset, yoffset);      
    //Add to item list for later maintenance    
    workItemList << rectItem;
    workItemList << pText;        
  }   
  return 0;
}

void WidgetApp::Init()
{
  //Widget tests 
  Na2dperfCreateTestWidget(m_widgetTestInStruct);
}

void WidgetApp::Process()
{
  for(int i=0; i < workItemList.count();i ++)  
    workItemList[i]->moveBy(i*off,i*off);
  if(off>0)off=-5; else off=5;
  
  //Indicate that the processing is complete
  SetProcessCallComplete();
  
}
