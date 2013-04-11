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

#ifndef _HISTO_H
#define _HISTO_H

//Definition of Histo Widget
class HistoWidget: public QWidget
{
public:
  HistoWidget(int inMemory, QWidget* parent):
    QWidget(parent)
  {
	  memory = inMemory;
	  currX = 0;
	  for(int i=0;i < memory;i ++) points.append(QPointF(0,0));
  }
protected:  
  void paintEvent(QPaintEvent *event)
  {
	QBrush currBrush(Qt::darkRed);
	QBrush borderBrush(Qt::black);
	QPen borderPen(Qt::black,5.0);
	QPen currPen(Qt::yellow,1.0);

    QPainter painter;
    painter.begin(this);
	
    painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(currBrush);
	painter.setPen(currPen);
	painter.fillRect(painter.window(),currBrush);
	painter.setBrush(Qt::NoBrush);
	painter.setPen(borderPen);
	painter.drawRoundedRect(painter.window(), 5.0, 3.0);
	painter.setBrush(currBrush);
	painter.setPen(currPen);
	painter.drawText(QRectF(10,0,35,14),"Flow");
	painter.drawLines(points.toVector());

    painter.end();
  }
private:
	QList<QPointF> points;
	int memory;
	int currX;
public:
	void setVal(float newVal)
	{
		if(newVal < 0.01) newVal = height()/2;
		if(currX >= memory) currX = 0;
		points[currX].setX(currX);		
		points[currX].setY(height() - newVal);
		currX ++;
	};
}; 

#endif //HISTO_H
