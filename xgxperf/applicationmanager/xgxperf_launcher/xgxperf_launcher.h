/*****************************************************************************
 * xgxperf_launcher.h
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
#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtGui>
#include <QObject>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtWidgets/QApplication>

#define ICON_UNIT_WIDTH 150
#define MAX_ICONS_PER_ROW 3
#define ICON_ROW_HEIGHT 200

class xgxPerfConfigParams
{
public:
	QString iconName;
	QString iconLabel;
	QString appName;
	QString appParameters;
	QString appParameters2;
};


//Create new class for view
class View : public QGraphicsView
{
public:
    View(QGraphicsScene *scene) : QGraphicsView(scene) { }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event); //always
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};


class iconWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    iconWidget(QGraphicsItem *parent = 0, xgxPerfConfigParams *config=0,
			QGraphicsTextItem* pResultWin=0) //just this one time :(
        : QGraphicsWidget(parent)
    {
        setCacheMode(DeviceCoordinateCache);
	buttonPixmap = QPixmap(config->iconName);
	if(buttonPixmap.isNull())
		qDebug() << "Couldnt open icon image file!";
	else
	        buttonPixmap = buttonPixmap.scaled(96,64);
        buttonName = config->iconLabel;
        setAcceptHoverEvents(true);
        currConfig = config;
	pResultItem = pResultWin;
	 currParent = parent;
    }

    QRectF boundingRect() const
    {
        return QRectF(0, 0, 128, 128 + 25);
    }

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addRect(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
    {
        bool down = option->state & QStyle::State_Sunken;
        bool over = option->state & QStyle::State_MouseOver;
        QFont textFont = QFont(QString("Tahoma"),12);
        textFont.setBold(true);  

        QRectF r = boundingRect();
        QLinearGradient grad(r.topLeft(), r.bottomRight());
        grad.setColorAt(1, Qt::black );
        grad.setColorAt(0, QColor(35,143,192,255) );        
        painter->setPen(Qt::white);
        painter->setBrush(grad);      
        
        if(down || over)              
          painter->drawRoundedRect(r.x(), r.y(), r.width(), r.height(), 15,15);
        else
          painter->drawRoundedRect(r.x()+5, r.y()+5, r.width()-10, r.height()-10, 15,15);        
        painter->setFont(textFont);         
        painter->setPen(Qt::white);                
	if(!buttonPixmap.isNull())
	{
          painter->drawPixmap(16,16, buttonPixmap);
          painter->drawText(16,16+buttonPixmap.height()+25, buttonName);                 
	}
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *)
{
  QProcess runApp;
  QStringList tempStringList;
  QStringList appFinalParams;
  QString appFinalCmd;
  QString testcase;

#ifndef Q_WS_WIN
  appFinalCmd.append("./");
  appFinalCmd.append(currConfig->appName);
#endif

#ifdef Q_WS_QWS
  appFinalParams<< "-qws";
#endif

  appFinalParams << currConfig->appParameters.split(" ");
  appFinalParams << currConfig->appParameters2;
  //qDebug() << "App string list is " << appFinalParams;

  runApp.execute(appFinalCmd, QStringList(appFinalParams));
  runApp.close();    
  //update result
  QFile profile("profiledata_123.xml");
  if(profile.exists())
  {
    profile.open(QIODevice::ReadOnly | QIODevice::Text);  
    QXmlStreamReader profileStream(&profile);
    pResultItem->setPlainText(getParamsFromXmlStream(profileStream));    
    profile.close();
  }  
  else
    pResultItem->setPlainText("Status Window: \n Error: Operation did not complete.");  
      update();
      QPaintEvent event(QRect(0,0,460,620));
      QCoreApplication::sendEvent(QApplication::desktop(), &event);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
    {
        update(); //ensure overlay is removed
    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *)
    {
        update(); //ensure overlay is removed
    }


private:
    QPixmap buttonPixmap;
    QGraphicsItem* currParent;
    QString buttonName;
    int appID;
    xgxPerfConfigParams* currConfig;
    QGraphicsTextItem* pResultItem;
    QString getParamsFromXmlStream(QXmlStreamReader& reader)
    {
	QString resultString;
	while (!reader.atEnd()) 
	{
		reader.readNext();
		if (reader.isStartElement()) 
		{
		    if(reader.name().toString() == "Preconfigured_Test_Name")
		    {
			resultString.append("Benchmark Configuration = ");
		        resultString.append(reader.readElementText());
			resultString.append("\n\n");
		    }
		    if(reader.name().toString() == "Screen_Creation_Time_mS")
		    {
			resultString.append("Screen Creation Time (ms) = ");
		        resultString.append(reader.readElementText());
			resultString.append("\n\n");
		    }
		    if(reader.name().toString() == "Average_CPU_Load_Percentage")
		    {
			resultString.append("Average CPU Load (%) = ");
		        resultString.append(reader.readElementText());
			resultString.append("\n");
		    }
		}
	}
	return resultString;
    };
};


#endif //LAUNCHER_H
