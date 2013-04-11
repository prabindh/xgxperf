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

#ifndef _THERMO_H
#define _THERMO_H

#include "../applicationmanager/common/applicationbase.h"


class ThermoClass: public QWidget
{
public:
	ThermoClass(QWidget* parent=0, QRectF inRect=QRectF(0,0,0,0), 
        float percentVal = 0.0): QWidget(parent)
	{
		currRect = inRect;
		currVal = percentVal;
		move(inRect.x(), inRect.y());
	};
     QRectF boundingRect() const
     {
         return currRect;
     };
	 void setTempVal(float newVal) {currVal = newVal;update();};
protected:
	void paintEvent ( QPaintEvent * event)
	{
		QPainter painter(this);		
    QPen currPen(Qt::white, 4.0);
    
    QLinearGradient fade(0, 0, currRect.width(),0);
    fade.setColorAt(0, QColor(255, 0, 0, 255));
    fade.setColorAt(0.4, QColor(255, 128, 128, 255));    
    fade.setColorAt(0.5, QColor(255, 255, 255, 255));
    fade.setColorAt(0.6, QColor(255, 128, 128, 255));        
    fade.setColorAt(1, QColor(255, 0, 0, 255));
    
    QBrush currBrush(fade);//Qt::red);
    event=0;		

    painter.fillRect(0, (1.0-currVal)*currRect.height(), currRect.width(), 
                        currRect.height(), currBrush);
    for(int i=0;i < currRect.height();i += currRect.height()/10)
      painter.drawLine(QPoint(currRect.width()/3,i), QPoint(currRect.width()/3+5,i));                             		
  };

	void  resizeEvent ( QResizeEvent * event )
	{
    event=0;	
    QRegion r1(QRect(currRect.width()/3, 0, currRect.width()/3, currRect.height()));
    QRegion r2(QRect(0, currRect.height()-10, 
            currRect.width(), currRect.width()), QRegion::Ellipse);     
    QRegion r4 = r1.united(r2);

		setMask(r4);
	}

private:
	QRectF currRect;
	float currVal;
};

#endif