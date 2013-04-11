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

#ifndef _ECGMONITOR_H
#define _ECGMONITOR_H

#include "../applicationmanager/common/applicationbase.h"

//Definition of QWidget subclass
class Na2dperfWidget: public QWidget
{
public:
  Na2dperfWidget(QWidget* parent):
    QWidget(parent){}
protected:  
  void paintEvent(QPaintEvent *event)
  {
	const QPointF points[] = {
     	QPointF(10.0, 80.0),
	     QPointF(m_offset+20.0, 100.0),
	     QPointF(m_offset+80.0, 230.0),
	     QPointF(m_offset+100.0, 210.0),
	     QPointF(m_offset+110.0, 330.0),
	     QPointF(m_offset+120.0, 210-m_offset),
	     QPointF(m_offset+160.0, 330.0),
	     QPointF(m_offset+240.0, 210.0),
	     QPointF(m_offset+250.0, 330.0-m_offset),
	     QPointF(m_offset+300.0, 330.0),
	     QPointF(m_offset+320.0, 210.0),
	     QPointF(420.0, 250.0),
	     QPointF(430.0, 210.0),
	     QPointF(460.0, 300.0),
	     QPointF(490.0, 300.0),
	 };
	QBrush currBrush(Qt::darkRed);
	QPen currPen(Qt::yellow,3.0);
	QFont titleFont("Helvetica",25);
	QFont textFont("Helvetica",12);
	QPen monitorPen(Qt::white,2.5,Qt::DotLine);

    QPainter painter;
    painter.begin(this);
	painter.setBrush(currBrush);
	painter.setPen(currPen);
    painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(painter.window(),currBrush);
	 painter.drawPolyline(points, 14);    
	painter.drawLine(0.0,320.0, 500.0,320.0);
	painter.setFont(titleFont);
    painter.drawText(QRect(20,10, 300, 100), Qt::AlignTop, 
                QString("ECG Monitor"));            
	painter.setFont(textFont);
    painter.drawText(QRect(250,30, 400, 100), Qt::AlignTop, 
                QString("Beat: 120/120"));
    painter.drawText(QRect(250,45, 400, 150), Qt::AlignTop, 
                QString("Pressure: Normal"));
    painter.drawText(QRect(250,60, 400, 250), Qt::AlignTop, 
                QString("Vitals: Normal"));                        
    painter.drawText(QRect(250,75, 400, 250), Qt::AlignTop, 
                QString("Temperature: deg/C"));                        
    painter.drawText(QRect(250,90, 400, 250), Qt::AlignTop, 
                QString("Neuro Activity: Normal"));                        
    painter.drawText(QRect(250,105, 400, 250), Qt::AlignTop, 
                QString("Overall Status: Ok"));                        



	painter.setPen(monitorPen);
	painter.drawLine(0.0,210-m_offset, 500.0,210-m_offset);
    painter.end();
  }
private:
  float m_offset;
public:
	void setOffset(int offset){m_offset = offset;};
}; 


class EcgMonitorApp: public ApplicationBase
{    
public:
    EcgMonitorApp(QWidget* parent, QRectF inSceneRect, QGraphicsScene *scene,
        void* data);   
    void Init();    
    void Process();        
    QString GetAppName();                
    QIcon GetAppIcon();              
    int GetSwitchingTime();         
private:
	Na2dperfWidget *pMonitorWidget;
    int currTimerCount;
    TestTargetParamsStruct* m_widgetTestInStruct;
};                                                                               

#endif
