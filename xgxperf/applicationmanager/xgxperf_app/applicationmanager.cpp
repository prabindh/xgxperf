/*****************************************************************************
 * applicationmanager.cpp
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
 
#include "applicationmanager.h"

#include <QtGui>
#include <QtWidgets/QPushButton>

#define MAX_NUM_PREBUILT_APPS (8)
QString appNameList[MAX_NUM_PREBUILT_APPS] = {"automation", "widget", "glwidget", "browser","ecgmonitor","autoscreen","vslib", "sewingmachine"};
TestTargetParamsStruct g_widgetTestData;
TestResultsDataStruct g_widgetOutputPerformanceData;
QString currCookie;
///////////////////////
ApplicationManager::ApplicationManager(QWidget *parent, QList<int> paramList, 
                        QString targetAppName, QString inCookie): 
QGraphicsView(parent)
{
    currScreenWidth = size().height();
    currScreenHeight = size().width();    
    
    pTimer1 = new QTimer(this);
    connect(pTimer1, SIGNAL(timeout()), this, SLOT(TimerAnimate()));
    pTimer1->start(2000); 

    //load test widget after setting the test parameters
    memset(&g_widgetTestData, 0, sizeof(g_widgetTestData));
    
    currCookie = inCookie;
    g_widgetTestData.num_widgets = paramList[0];
    g_widgetTestData.effects = paramList[1];
    g_widgetTestData.transparent = paramList[2];
    g_widgetTestData.type_texture = paramList[3];
    g_widgetTestData.size_font = paramList[4];            
    g_widgetTestData.rate_screen_refresh_fps = paramList[5];      
    g_widgetTestData.size_widget = paramList[7];            
    g_widgetTestData.target_num_frames = paramList[8];  
        
    setupScene();  
    setScene(&m_scene);
 
    m_scene.update();
    //load and start the app
    //targetAppName with prebuilt ID or new one
    if(paramList[6] < MAX_NUM_PREBUILT_APPS)
          targetAppName = appNameList[paramList[6]];
    if(!loadTargetApp(targetAppName))
      exit(-1);
    m_currAppName = targetAppName;
}

/**
 * This loads a new application into the manager
 */                                                               
typedef ApplicationBase* (*PCREATENEWAPP)(QWidget* parent, QRectF inSceneRect, 
          QGraphicsScene *scene, void* data);


bool ApplicationManager::loadTargetApp(QString name)
{
  QLibrary XgxperfLib(name);

  PCREATENEWAPP pCreateNewApp = (PCREATENEWAPP) XgxperfLib.resolve("createNewApp");
  
  if (pCreateNewApp)
  {
    appList << pCreateNewApp(this, QRectF(0,10,currScreenWidth,
                    currScreenHeight-AM_ICON_HEIGHT-20),&m_scene,
                    (void*)&g_widgetTestData);
    return true;
  }
  else {qDebug() << name << " resolve failed"; return false;} 
}


/**
 * Set up the scene - its icon labels for now. The application workspace will be 
 * populated by the respective applications during the process call.  
 */
void ApplicationManager::setupScene()
{ 
  //Background
  //QRadialGradient gradient(0, 0, 30);
  //gradient.setSpread(QGradient::ReflectSpread);
  //m_scene.setBackgroundBrush(gradient);    
}

/**
 * For each tick, the registered application Process handler is invoked
 * Note that each application should have returned the right time at which it is 
 * supposed to be invoked during the registration process via GetSwitchingTime()   
 */
void ApplicationManager::TimerAnimate()
{
		if(appList[0]->isTargetNumFrameComplete())
		{
		  //exit
		  qDebug() << "writing op data";
      appList[0]->GetProfileParameters(&g_widgetOutputPerformanceData);		  
		  WriteOutputData();
		  qDebug() << "exiting";
		  exit(0);
		}        
}

void ApplicationManager::WriteOutputData()
{
  QString outfilename("profiledata_");
  outfilename.append(currCookie).append(".xml"); 
  //qDebug() << outfilename;
  QFile file(outfilename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
    qDebug() << "error opening xml file"; return;
  }
  QXmlStreamWriter stream(&file);
  stream.setAutoFormatting(true);
  stream.writeStartDocument();
  stream.writeStartElement("XgxPerf_Profile_Test_Inputs_Outputs");

  stream.writeTextElement("Preconfigured_Test_Name", m_currAppName);
  stream.writeTextElement("Num_Widgets", QString("%1").arg(g_widgetTestData.num_widgets));  
  stream.writeTextElement("Effects", QString("%1").arg(g_widgetTestData.effects));
  stream.writeTextElement("Transparency", QString("%1").arg(g_widgetTestData.transparent));
  stream.writeTextElement("Texture_type", QString("%1").arg(g_widgetTestData.type_texture));
  stream.writeTextElement("Font_Size", QString("%1").arg(g_widgetTestData.size_font));
  stream.writeTextElement("Screen_Refresh_Rate", 
                QString("%1").arg(g_widgetTestData.rate_screen_refresh_fps));
  stream.writeTextElement("Widget_Size", 
                QString("%1").arg(g_widgetTestData.size_widget));                
  stream.writeTextElement("Number_of_frames_run", 
                QString("%1").arg(g_widgetTestData.target_num_frames));
                                                                    
  stream.writeTextElement("Screen_Creation_Time_mS", QString("%1").arg(g_widgetOutputPerformanceData.initTime));
  stream.writeTextElement("Screen_Update_Time_Per_Frame_mS", QString("%1").arg(g_widgetOutputPerformanceData.processTime));  
  stream.writeTextElement("Average_CPU_Load_Percentage", QString("%1").arg(g_widgetOutputPerformanceData.averageLoad));  

  stream.writeEndElement();
  stream.writeEndDocument();
  file.close();

  /*  HTML file output */
  QString outfilename1("profiledata_");
  outfilename1.append(currCookie).append(".html"); 
  //qDebug() << outfilename1;
  QFile file1(outfilename1);  
  if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream htmlOut(&file1);
  htmlOut << "<HTML>XgxPerf_Profile_Test_Inputs<hr>";
  htmlOut << "<table border=\"1\">";
  htmlOut << "<tr><td>Preconfigured_Test_Name</td><td>";
  htmlOut << QString("%1").arg(m_currAppName) << "</td></tr>";
  htmlOut << "<tr><td>Num_Widgets</td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.num_widgets) << "</td></tr>";
  htmlOut << "<tr><td>Effects</td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.effects) << "</td></tr>";
  htmlOut << "<tr><td>Transparency </td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.transparent) << "</td></tr>";
  htmlOut << "<tr><td>Texture_type </td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.type_texture) << "</td></tr>";
  htmlOut << "<tr><td>Font_Size</td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.size_font) << "</td></tr>";
  htmlOut << "<tr><td>Screen_Refresh_Rate </td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.rate_screen_refresh_fps) << "</td></tr>";
  htmlOut << "<tr><td>Size_of_widgets </td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.size_widget) << "</td></tr>";
  htmlOut << "<tr><td>Number_of_frames_run </td><td>";
  htmlOut << QString("%1").arg(g_widgetTestData.target_num_frames) << "</td></tr>";
  htmlOut << "</table><hr><br>XgxPerf_Profile_Test_Output_Profile_Parameters<br>";
  htmlOut << "<table border=\"1\">";
  htmlOut << "<tr><td>Screen Init Time (mS)</td><td>" << g_widgetOutputPerformanceData.initTime << "</td></tr>";
  htmlOut << "<tr><td>Screen Update Time/Frame (mS)</td><td>" << g_widgetOutputPerformanceData.processTime << "</td></tr>";
  htmlOut << "<tr><td>Average CPU Load </td><td>" << g_widgetOutputPerformanceData.averageLoad << "</td></tr>";
  htmlOut << "</table>";    
  htmlOut << "</HTML>";
  file1.close();

  /*  RAW file output */
  QString outfilename3("profiledata_");
  outfilename3.append(currCookie).append(".txt"); 
  //qDebug() << outfilename3;
  QFile file3(outfilename3);  
  if (!file3.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream rawOut(&file3);
  rawOut << "XgxPerf_Profile_Test_Inputs<br><br>";
  rawOut << "Preconfigured_Test_Name = ";
  rawOut << m_currAppName;
  rawOut << "<br><br>Num_Widgets = ";
  rawOut << g_widgetTestData.num_widgets;
  rawOut << "<br><br>Effects = ";
  rawOut << g_widgetTestData.effects;
  rawOut << "<br><br>Transparency  =";
  rawOut << g_widgetTestData.transparent;
  rawOut << "<br><br>Texture_type  =";
  rawOut << g_widgetTestData.type_texture;
  rawOut << "<br><br>Font_Size =";
  rawOut << g_widgetTestData.size_font;
  rawOut << "<br><br>Screen_Refresh_Rate  =";
  rawOut << g_widgetTestData.rate_screen_refresh_fps;
  rawOut << "<br><br>Size_of_widgets  =";
  rawOut << g_widgetTestData.size_widget;
  rawOut << "<br><br>Number_of_frames_run  =";
  rawOut << g_widgetTestData.target_num_frames;
  rawOut << "<br><br>XgxPerf_Profile_Test_Output_Profile_Parameters";
  rawOut << "<br><br>Screen Init Time (mS) =" << g_widgetOutputPerformanceData.initTime;
  rawOut << "<br><br>Screen Update Time/Frame (mS) =" << g_widgetOutputPerformanceData.processTime;
  rawOut << "<br><br>Average CPU Load  =" << g_widgetOutputPerformanceData.averageLoad;
  file3.close();

  //Write to terminal also - for Matrix integration
  qDebug() << "XgxPerf_Profile_Test_Output_Profile_Parameters \n";
  qDebug() << "Screen Init Time (mS) =" << g_widgetOutputPerformanceData.initTime;
  qDebug() << "\nScreen Update Time/Frame (mS) =" << g_widgetOutputPerformanceData.processTime;
  qDebug() << "\nAverage CPU Load (%) = " << g_widgetOutputPerformanceData.averageLoad;


  //Write Screen dump also - writes to dump.tar.gz
#ifndef Q_WS_WIN 
  QProcess screendump;
  QStringList tempStringList;
  tempStringList << "get_screen_dump.sh";
  screendump.execute(QString("sh"),tempStringList);
  screendump.close();  
  QFile tempImageFile("dump.raw");
  if (!tempImageFile.open(QIODevice::ReadOnly))
    return;
  QByteArray tempImageArray = tempImageFile.readAll();
  tempImageFile.close();
  QImage tempImage((uchar*)tempImageArray.data(),currScreenWidth, currScreenHeight,QImage::Format_RGB16);
  tempImage.save(QString("dump_").append(currCookie).append(".png"),"PNG");
#endif  
}
