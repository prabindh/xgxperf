/*****************************************************************************
 * applicationbase.h
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


//#include <QtGui>
#include "stdio.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QTextEdit>
#include <QTimer>
#include <QtWidgets/QPushButton>
#include <QTime>
#include <QPainter>
#include <QList>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsProxyWidget>

#ifndef _APPBASE_H
#define _APPBASE_H

#ifndef Q_WS_WIN
#include "sys/time.h"
#include "unistd.h"
#endif

//Toggle information display on top
//Note that enabling this will shoot up the CPU utilisation due to blending
//#define _ENABLE_INFOLAYER


typedef struct
{
  int num_widgets;
  int size_font;
  int size_texture;
  int type_texture;
  int transparent;
  int effects;  
  int rate_screen_refresh_fps;
  int num_blending_layers; 
  int size_widget;
  int target_num_frames;
  void* extensions;
} TestTargetParamsStruct;

typedef struct
{
  int initTime;
  int processTime;
  int averageLoad;
}TestResultsDataStruct;


class ApplicationBase : public QWidget
{
  Q_OBJECT
public:
    /** Store the scene and the rectangle for later use */
    ApplicationBase(QWidget* parent, QRectF inSceneRect, 
                        QGraphicsScene *scene, void* data=0) : 
    QWidget(parent)
    {        
      m_scene = scene; 
      m_parent = parent;
      sceneRect = inSceneRect;
	   currLoadAccumulate = 0;
	   currAccumulatedProcessTime = 0;
	   currProcessCallCount = 0;
      //Store the test data locally
	   m_widgetTestInStruct = (TestTargetParamsStruct*)data;    
	   pProcessTimer1 = new QTimer();
      connect(pProcessTimer1, SIGNAL(timeout()), this, SLOT(ProcessTimerSlot()));
      pProcessTimer1->start(1000/m_widgetTestInStruct->rate_screen_refresh_fps);
	   m_inited = false;
	   m_currProcessCompleted = true;
	pLoadCheckTimer = new QTimer();
      connect(pLoadCheckTimer, SIGNAL(timeout()), this, SLOT(LoadCheckTimerSlot()));
      pLoadCheckTimer->start(2000);
	currLoadAccumulateCount = 0;
#ifndef Q_WS_WIN	
	currJiffies = 0;	
#endif 	
    }
    /**called once by ApplicationManager */        
    virtual void Init(){};    
    /** ApplicationManager calls this every screen switch period returned earlier
     * in GetSwitchingTime */                 
    virtual void Process(){};                      
    /**ApplicationManager calls this when app is required to exit - override 
     *when needed */                        
    virtual void Exit()
    {             
      for(int i=0;i < workItemList.count();i ++)  
      {
        m_scene->removeItem(workItemList[i]);    
        //TODO: fix deletion of needed info
        delete workItemList[i];          
      }            
      workItemList.clear();
      for(int i=0;i < proxyWorkItemList.count();i ++)  
      {
        //TODO: fix deletion of needed info
        delete proxyWorkItemList[i];          
      }            
      proxyWorkItemList.clear();
    }    
	/** Retrieve the profile parameters */
	void GetProfileParameters(TestResultsDataStruct* pD){
		pD->initTime=currInitTime;
		pD->processTime=(currAccumulatedProcessTime/(currProcessCallCount+1));
		pD->averageLoad=(currLoadAccumulate*100)/(currLoadAccumulateCount+1);};
	/** App manager calls this at intervals */
	bool isTargetNumFrameComplete(){
	   //qDebug() << "isTargetNumFrameComplete called, currProcessCallCount=" << currProcessCallCount;
    return (currProcessCallCount >= m_widgetTestInStruct->target_num_frames);};
	/**Holds list of all items in the current app, use this for clean up in Exit*/
    QList<QGraphicsItem *> workItemList;     
    QList<QGraphicsProxyWidget *> proxyWorkItemList;  
    /**Parent scene - Use this to add the applications items */
    QGraphicsScene *m_scene;
    /**Work area rectangle for this application*/
    QRectF sceneRect;     
    /**Parent widget */
    QWidget *m_parent;
  /** Async applications call this to indicate their processing is waiting */
  void SetProcessCallWaiting(){m_currProcessCompleted = false;};
  /** Async applications call this to indicate their processing is complete */
	void SetProcessCallComplete(){PostProcessCall();};        
private:
	/** Start the process timer */
	void PreProcessCall(){
    m_currProcessCompleted=false; /* TODO: race */   
    processProfileTime.start();};
	void PostProcessCall(){ 
		m_currProcessCompleted=true;
		m_thisFrameProcessTime = processProfileTime.elapsed();
		currAccumulatedProcessTime += m_thisFrameProcessTime;
		updateInfoLayer();
		currProcessCallCount++; 
		//qDebug() << "currProcessCallCount = " << currProcessCallCount;
		if(currProcessCallCount >= m_widgetTestInStruct->target_num_frames) 
		    {
		      pProcessTimer1->stop();
		      pLoadCheckTimer->stop();
		    }
		};
	/** Start the process timer */
	void PreInitCall(){ initProfileTime.start();};

	QTextEdit* infoLayer;
	QPushButton* toggleSwitch;
	void CreateInfoLayer()
	{
#ifdef _ENABLE_INFOLAYER
	  //Toggle button
	  toggleSwitch = new QPushButton("Info ON");
	  toggleSwitch->move(10 ,10 );
	  toggleSwitch->setCheckable(true);
	  QGraphicsItem *tempItem1 = m_scene->addWidget(toggleSwitch);
	  tempItem1->setZValue(15);
	  workItemList << tempItem1;
	  
	  //Info layer
	 	  infoLayer = new QTextEdit();
	  infoLayer->move(50,50);
	  infoLayer->resize(250,90);
	  infoLayer->setWindowOpacity(0.5);
	  infoLayer->setFontPointSize(16);
	  infoLayer->setTextColor(Qt::blue);
	  infoLayer->setFontWeight(QFont::Bold);
	  QString infoText;
	  infoText = QString("Statistics: \nProcess Time = %1 mS \nInit Time = %2 mS \nCPU Load = %3").arg(m_thisFrameProcessTime).arg(currInitTime).arg(m_thisFrameLoad);
	  infoLayer->setText(infoText);
	  QGraphicsItem *tempItem = m_scene->addWidget(infoLayer);
	  tempItem->setZValue(15);
	  workItemList << tempItem;
	  //Switch off by default
	  infoLayer->setVisible(false);
#endif
	}
	void updateInfoLayer()
	{
#ifdef _ENABLE_INFOLAYER
	  QString infoText;
	  infoText = QString("Statistics: \nProcess Time = %1 mS \nInit Time = %2 mS \nCPU Load = %3").arg(m_thisFrameProcessTime).arg(currInitTime).arg(m_thisFrameLoad);
	  infoLayer->setText(infoText);

	  if(toggleSwitch->isChecked())
	  {
	    toggleSwitch->setText("Info OFF");
	    infoLayer->setVisible(true);
	  }    
	  else
	  {
	    toggleSwitch->setText("Info ON");	  
	    infoLayer->setVisible(false);	    
	  }
#endif
	}
	void PostInitCall(){ currInitTime = initProfileTime.elapsed(); CreateInfoLayer();};
	/** Process time maintainers */
	QTime processProfileTime;
	int currAccumulatedProcessTime;
	/** Init time maintainers */
	QTime initProfileTime;
	int currInitTime;
	/** CPU Load maintainers */
	float currLoadAccumulate;
	unsigned int currLoadAccumulateCount;
	int m_thisFrameProcessTime;
	float m_thisFrameLoad;
#ifndef Q_WS_WIN
	timeval startTime, endTime;
	unsigned long currJiffies;
	unsigned long prevJiffies;
	unsigned long long prevIdleTime,prevUsedTime, idleTime, usedTime;
#endif
	/** NumFrames */
	int currProcessCallCount;
	TestTargetParamsStruct* m_widgetTestInStruct;
	bool m_inited;
	/** Asynchronous slot handler */
	bool m_currProcessCompleted;
	QTimer *pProcessTimer1;
	QTimer *pLoadCheckTimer;
public slots:
	/** Process Timer handler */
	void ProcessTimerSlot(){	
		  //qDebug() << "process timer called";
		if(!m_inited){		
			PreInitCall();
			Init();
			PostInitCall();
			m_inited = true;}
		if(m_currProcessCompleted) /*Do this if previous proc is complete*/{
			//  qDebug() << "process called";
  		PreProcessCall();
  		Process();
  		  //PostProcessCall() is called from setProcessComplete itself
    		}
		//qDebug() << "process completed";        
  	}
	/** Load check Timer handler */
	void LoadCheckTimerSlot(){	
#ifndef Q_WS_WIN
		unsigned long diffTime2;
		FILE *procFile = fopen("/proc/stat", "r");
		unsigned char procName[200]; //TODO: length
		unsigned int currTime1, currTime2, currTime3,temp;
		float elapsedTimeMS;

		if(procFile)
		{
			temp=fscanf(procFile, "%s\t%d\t%d\t%d\n", procName, &currTime1, &currTime2, &currTime3);
			temp=0;
			fclose(procFile);
		}
		prevJiffies = currJiffies;
		currJiffies = (currTime1+currTime2+currTime3);
		//convert to real time ms
		elapsedTimeMS = 1000*((float)(currJiffies-prevJiffies)/(float)sysconf(_SC_CLK_TCK));

		memcpy(&startTime, &endTime, sizeof(timeval));
		gettimeofday(&endTime, NULL);
		diffTime2 = (endTime.tv_sec - startTime.tv_sec) * 1000 +
			(endTime.tv_usec - startTime.tv_usec) / 1000;
	
		//qDebug() << "eltime = " << elapsedTimeMS << "cpuload = " << (elapsedTimeMS/diffTime2);
		m_thisFrameLoad = (elapsedTimeMS/diffTime2);
		currLoadAccumulate += m_thisFrameLoad;

		currLoadAccumulateCount ++;
#endif		
	}
};

#endif
