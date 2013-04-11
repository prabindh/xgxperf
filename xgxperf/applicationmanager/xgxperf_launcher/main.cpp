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
#include <QTime>

#include "xgxperf_launcher.h"

QTime showTime;

QList<xgxPerfConfigParams*> xgxPerfConfigParamsList;

//Form screen from config list
void screenFromQuery(QGraphicsItem* pParent, QGraphicsTextItem* pResultWin)
{
    int currX = 0, currY = 100;
    if(xgxPerfConfigParamsList.count() == 0) return;
    for(int i = 0;i < xgxPerfConfigParamsList.count();i ++)
    {
	iconWidget *currWidget = new iconWidget(pParent, xgxPerfConfigParamsList[i], pResultWin);
	currWidget->setPos(currX, currY);
	currX += ICON_UNIT_WIDTH;
	if(currX >= MAX_ICONS_PER_ROW*ICON_UNIT_WIDTH){currX = 0;currY += ICON_ROW_HEIGHT; }
	if(i >= 5) break; //2 rows only for now
    }
}

//Get config from xml file
void queryFromConfigStream(QXmlStreamReader& reader)
{
   xgxPerfConfigParams* inParams;
   QString currVal1, currVal2, currName;
    while (!reader.atEnd()) 
    {
        reader.readNext();
        if (reader.isStartElement()) {
            if(reader.name() == "object")
	    {
                currVal1 = reader.attributes().value("type").toString();
		//qDebug() << "object type = " << currVal1;
		inParams = new xgxPerfConfigParams;
		xgxPerfConfigParamsList << inParams;
	    }
	    else if(reader.name() == "param")
	    {
                currName = reader.attributes().value("name").toString();
                currVal2 = reader.attributes().value("value").toString();
		//qDebug() << "param name = " << currName << " ,value = " << currVal2 ;		
		if(currName == "iconName") inParams->iconName = currVal2;
		else if(currName == "iconLabel") inParams->iconLabel = currVal2;
		else if(currName == "appName") inParams->appName = currVal2;
		else if(currName == "appParameters") inParams->appParameters = currVal2;
		else if(currName == "appParameters2") inParams->appParameters2 = currVal2;
	    }
        }
    }
    if (reader.hasError()) {
        qDebug() << "  Error in HTML file formation" << reader.errorString();
    }
}

#define USAGE_STRING "xgxperf_launcher is a GUI wrapper over xgxperf_app \
benchmarking application. \nUsage:\nxgxperf_launcher [-qws] config.html\n"

/**
 Main function
**/
int main(int argc, char **argv)
{

    showTime.start();
    
#ifdef Q_WS_QWS
    if(argc < 3) {qDebug() << USAGE_STRING; exit(-1);}
    QString configFileName = QString(argv[2]);
#else
    if(argc < 2) {qDebug() << USAGE_STRING; exit(-1);} 
    QString configFileName = QString(argv[1]);
#endif
    QFile file(configFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "  Xgxperf_launcher:: Couldn't open the config file (" << configFileName << ")";
        return -1;
    }
   
    QApplication app(argc, argv);
    int screenWidth = app.desktop()->screenGeometry().width();
    int screenHeight = app.desktop()->screenGeometry().height();    
    QLinearGradient backGradient(0,0,0,screenHeight);


    backGradient.setColorAt(0, QColor(35,143,192,255));
    backGradient.setColorAt(0.2, Qt::black );        
    backGradient.setColorAt(1, QColor(35,143,192,255));    

    QGraphicsScene scene(0, 0, 460, 620);

    QGraphicsItem *iconWidgetParent = new QGraphicsRectItem;

    //Add parent widget to scene
    scene.addItem(iconWidgetParent);
    iconWidgetParent->setScale(1.0);    
    iconWidgetParent->setPos(0,0);
    
    //Draw the text at top
    QGraphicsTextItem *pTextItem = new QGraphicsTextItem("XgxPerf Toolkit");
    QFont titleFont("Tahoma",36); 
    pTextItem->setFont(titleFont);
    pTextItem->setPos(50,10);
    pTextItem->setDefaultTextColor(Qt::white);
    scene.addItem(pTextItem);

    //Result/ notification at the bottom
    QFont textFont = QFont(QString("Tahoma"),14);        
    QGraphicsTextItem* pResultItem = new QGraphicsTextItem("Status Window: \n Click on an icon to start benchmarking...", 0);
    pResultItem->setFont(textFont);
    pResultItem->setDefaultTextColor(Qt::white);
    scene.addItem(pResultItem);
    pResultItem->moveBy(0, 500);

    QXmlStreamReader reader(&file);
    queryFromConfigStream(reader);
    screenFromQuery(iconWidgetParent, pResultItem);

    //Create final view    
    View *view = new View(&scene);
    view->setBackgroundBrush(backGradient);    
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "XgxPerf Benchmark Launcher"));
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    
    
    qDebug() << "showtime before view->show()" << showTime.elapsed();    
    view->show();
    return app.exec();
}

