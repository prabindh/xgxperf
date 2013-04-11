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

#ifndef _TURBINE_H
#define _TURBINE_H

#include "../applicationmanager/common/applicationbase.h"


class TurbineClass: public QWidget
{
public:
	TurbineClass(QWidget* parent=0, QRectF inRect=QRectF(0,0,0,0), 
        QString inText="", 
        QRegion::RegionType inMask=QRegion::Rectangle): QWidget(parent)
	{
		currRect = inRect;
		currText = inText;
		currMask = inMask;
		move(inRect.x(), inRect.y());
	};
     QRectF boundingRect() const
     {
         return currRect;
     };
	 void setText(QString newText) {currText = newText;};
protected:
	void paintEvent ( QPaintEvent * event)
	{
    event=0;	
		QPainter painter(this);		
    QPen currPen(Qt::black, 4.0);		

    painter.drawRoundedRect(0, 0, currRect.width(), currRect.height(), 5, 5);    

    QLinearGradient fade(0, 0, 0, currRect.height());
    fade.setColorAt(0, QColor(0, 0, 0, 255));
    fade.setColorAt(1, QColor(255, 255, 255, 255));
    painter.fillRect(0,0,currRect.width(),currRect.height(), fade);
		    
    painter.setPen(currPen);            
		painter.drawText(0, 0, currRect.width(), currRect.height(), Qt::AlignCenter, currText);
  };

	void  resizeEvent ( QResizeEvent * event )
	{
    event=0;	
    QRegion maskedRegion(0, 0, currRect.width(), currRect.height(), currMask);
		setMask(maskedRegion);
	}

private:
	QRectF currRect;
	QString currText;
	QRegion::RegionType currMask;
};


#endif