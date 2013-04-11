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

#ifndef _AUTOMATION_H
#define _AUTOMATION_H

#include "../applicationmanager/common/applicationbase.h"

#include "infobox.h"
#include "histo.h"

#include "../classes/qgraphicssvgnativeitem/qgraphicssvgnativeitem.h"

#include "math.h"

class AutomationApp: public ApplicationBase
{    
public:
    AutomationApp(QWidget* parent, QRectF inSceneRect, QGraphicsScene *scene,
        void* data);   
    void Init();    
    void Process();        
    QString GetAppName();                
    QIcon GetAppIcon();              
    int GetSwitchingTime();         
private:

    int currTimerCount;
	float needle1Angle;
	float needle2Angle;
	float needle3Angle;
	float fan1Angle;
	int arrowPos;
	HistoWidget* pHistoWidget;
	HistoWidget* pHistoWidget1;
	HistoWidget* pHistoWidget2;
	HistoWidget* pHistoWidget3;
	InfoBoxClass* pValveText1;
	InfoBoxClass* pValveText2;
    QGraphicsSvgNativeItem* pArrow1;
    QGraphicsSvgNativeItem* pFan;
    QGraphicsSvgNativeItem* pFan1;
    QGraphicsSvgNativeItem* pBoiler;
    QGraphicsSvgNativeItem* pBoiler1;
    QGraphicsSvgNativeItem* pBoilerPipe1;
    QGraphicsSvgNativeItem* pBoilerPipe2;
    QGraphicsSvgNativeItem* pBoilerPipe3;
    QGraphicsSvgNativeItem* pBoilerPipe4;
    QGraphicsSvgNativeItem* pBoilerPipe5;
    QGraphicsSvgNativeItem* pBoilerPipe6;
    QGraphicsSvgNativeItem* pBoilerPipe7;
    QGraphicsSvgNativeItem* pBoilerPipe8;
    QGraphicsSvgNativeItem* pBoilerPipe9;
    QGraphicsSvgNativeItem* pBoilerPipe10;
    QGraphicsSvgNativeItem* pChamber;
    QGraphicsSvgNativeItem* pChamber1;
    QGraphicsSvgNativeItem* pChamber2;
    QGraphicsSvgNativeItem* pChamber3;
    QGraphicsSvgNativeItem* pPipe1;
    QGraphicsSvgNativeItem* pPipe2;
    QGraphicsSvgNativeItem* pLBend1;
    QGraphicsSvgNativeItem* pLBend2;
    QGraphicsSvgNativeItem* pMeter1Needle1;
    QGraphicsSvgNativeItem* pMeter1Needle2;
    QGraphicsSvgNativeItem* pMeter1Needle3;
    QGraphicsSvgNativeItem* pMeter1Needle4;
    QGraphicsSvgNativeItem* pMeter1;
    QGraphicsSvgNativeItem* pMeter2;
    QGraphicsSvgNativeItem* pMeter3;
    QGraphicsSvgNativeItem* pMeter4;
    QGraphicsSvgNativeItem* pValve1;
    QGraphicsSvgNativeItem* pValve2;
    QGraphicsSvgNativeItem* pBottle1;
    QGraphicsSvgNativeItem* pBottle2;
    QGraphicsSvgNativeItem* pBottle3;
    QGraphicsSvgNativeItem* pBottle4;
    QGraphicsSvgNativeItem* pBottle5;
    QGraphicsSvgNativeItem* pBottle6;
    QGraphicsSvgNativeItem* pBottle7;
    QGraphicsSvgNativeItem* pBottle8;
    float bottlePos;
    float bottleYPos;
    TestTargetParamsStruct* m_widgetTestInStruct;

};                                                                               

#endif
