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

#include "ui_mainwindow.h"
#include "../applicationmanager/common/applicationbase.h"

class SewingMachineApp: public ApplicationBase, private Ui::MainWindow
{    
public:
    SewingMachineApp(QWidget* parent, QRectF inSceneRect, QGraphicsScene *scene,
        void* data);   
    void Init();    
    void Process();        
    QString GetAppName();                
    QIcon GetAppIcon();              
    int GetSwitchingTime();         
private:
    QGraphicsPixmapItem *pRotor1;    
    QGraphicsPixmapItem *pRotor2;     
    QGraphicsTextItem *pTemperatureVal;
    QGraphicsRectItem *pLiquidTank;    
    QGraphicsTextItem *pSpeedVal;    
    QGraphicsTextItem *pSpeedVal1;               
    int currTimerCount;
    QTransform currXfm;
    QGraphicsPixmapItem *pRotor1Rotated;            
    QGraphicsPixmapItem *pRotor2Rotated;       
    QDial *pDial;         
    QGraphicsRectItem *rotorSpeedItem;
    TestTargetParamsStruct* m_widgetTestInStruct;
};                                                                               

#endif