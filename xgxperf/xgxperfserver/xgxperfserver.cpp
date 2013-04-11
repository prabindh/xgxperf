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



#include <QtGui>
#include <QtNetwork>

#include "xgxperfserver.h"

#define CURRENT_IP_ADDR "172.24.191.40"
#define MAX_PARAM_NUM 100
QString paramList[MAX_PARAM_NUM];
QString currCookie, currDynamicAppName, processErrorMsg;
XgxPerfServer::XgxPerfServer(QWidget *parent, QString ipaddress, int portId)
    : QDialog(parent)
{
    textLabel = new QLabel(tr("starting"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textLabel);
    setLayout(mainLayout);

        connect(&tcpServer, SIGNAL(newConnection()),
            this, SLOT(connectionAvailable()));
        currIPAddress = ipaddress;//QString(CURRENT_IP_ADDR);
        currPort = portId;
        qDebug() << "Listening at IP " << currIPAddress << " at port " << portId;
if(start(currIPAddress, portId))
    exit(-1);
}

int XgxPerfServer::start(QString hostAddress, int portId)
{
    if(!tcpServer.isListening() && !tcpServer.listen(QHostAddress(hostAddress), portId))
        {
        qDebug() << "Error listening";
                textLabel->setText("Error listening");
        return 1;
        }
        textLabel->setText("Listening");
        return 0;
}


void XgxPerfServer::connectionAvailable()
{
    tcpSocket = tcpServer.nextPendingConnection();

    QFile file1("referrerlog.txt");
    if (!file1.open(QIODevice::Append | QIODevice::Text))
      return;
    QTextStream referrerOut(&file1);
    referrerOut << "\n" << tcpSocket->peerAddress().toString();
    file1.close();

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataOnSocket()));
}

int XgxPerfServer::retrieveFormContentDataIndex(const QByteArray line)
{
  if(line.contains("SW_PLATFORM_ID")) return 0;
  if(line.contains("HW_PLATFORM_ID")) return 1;
  if(line.contains("APP_ID")) return 2;
  if(line.contains("REFRESH")) return 3;
  if(line.contains("NUM_FRAMES")) return 4;
  if(line.contains("NUM_WIDGETS")) return 5;
  if(line.contains("WIDGET_SIZE")) return 6;
  if(line.contains("EFFECTS")) return 7;
  if(line.contains("BLENDING")) return 8;
  if(line.contains("TYPE_TEXTURE")) return 9;
  if(line.contains("FONT_SIZE")) return 10;
  if(line.contains("SGXPERF_USECASE")) return 11;
 if(line.contains("SGXPERF_NUM_OBJECTS")) return 12;
  if(line.contains("SGXPERF_TEXTURE_WIDTH")) return 13;
  if(line.contains("SGXPERF_TEXTURE_HEIGHT")) return 14;
  if(line.contains("SGXPERF_ROTATION")) return 15;
  if(line.contains("SGXPERF_PIXEL_FORMAT")) return 16;
  if(line.contains("SGXPERF_SURFACE_TYPE")) return 17;

  return -1;
}

int XgxPerfServer::parseRequest()
{
        int handler=0;
        QString postString;
        int lineNum = 0, paramNum;

        m_post_boundary = "INVALID_STRING_1234";
    foreach (const QByteArray &line, m_inData)
        {
           //qDebug() << "line=" << line;
       if (line.startsWith("GET"))
           {
                        textLabel->setText("Received GET data");
             m_parsedRequest = QUrl::fromPercentEncoding(line.mid(4).split(' ').at(0)).toLatin1();
                         handler=1; //GET
           }
       else if (line.startsWith("POST"))
           {
                        textLabel->setText("Received POST data");
              m_parsedRequest = QUrl::fromPercentEncoding(line.mid(5).split(' ').at(0)).toLatin1();
                          handler=2; //POST
           }
           else if(line.startsWith("Content-Type: multipart/form-data"))
           {
                          m_post_boundary = QUrl::fromPercentEncoding(line.split('=').at(1)).toLocal8Bit();
                          m_post_boundary.mid(m_post_boundary.lastIndexOf("-"));
                        //qDebug() << m_post_boundary;
                          //textLabel->setText(textLabel->text().append("Found Post Boundary"));
                          //textLabel->setText(textLabel->text().append(m_post_boundary));
           }
           else if(line.contains("Content-Disposition: form-data"))
           {
             QByteArray tempLine = m_inData[lineNum+2];
                   QString possibleParam = QUrl::fromPercentEncoding(tempLine).toLatin1();

                  paramNum = retrieveFormContentDataIndex(line);
      if(paramNum >= 0)
                         paramList[paramNum] = possibleParam.remove("\r\n");
                        else if(line.contains("DYN_PERF_FILE"))
        currDynamicAppName = possibleParam.remove("\r\n");
                        //textLabel->setText(textLabel->text().append(possibleParam));
                        //textLabel->setText(textLabel->text().append("\n"));
                        //qDebug() << possibleParam << paramNum;

           }
           else
           {
                        //textLabel->setText(textLabel->text().append(line));
           }
           lineNum ++;
        }
        return handler;
}

void XgxPerfServer::dataOnSocket()
{
        int timeout = 100, handler;
        QByteArray response;
        textLabel->setText("Received data");
    while((tcpSocket->canReadLine() && timeout))
    {
        //TODO: Make more dynamic
        m_inData.append(tcpSocket->readLine());
                timeout--;
    }

  //Parse request
  handler = parseRequest();
  if(handler == 1) //GET
  {
          response = formGETResponse();
  }
 else if(handler == 2)//POST
          response = formPOSTResponse();
  tcpSocket->write(response);
  //Clear the previous data
  m_inData.clear();
  m_parsedRequest.clear();
  /* TODO: Need to keep alive the socket only on keep-alive */
  //tcpSocket->close();
  //textLabel->setText("Sent data");
}

QByteArray XgxPerfServer::formGETResponse()
{
    QByteArray text, body;
    //QByteArray body = "<HTML>" + m_parsedRequest + "</HTML>\r\n\r\n";
        QString tempString(m_parsedRequest);


    text = QByteArray("HTTP/1.1 200 OK \r\n");

        if(tempString.contains(".xml"))
        {
                 QFile file(tempString.mid(1));
                 if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                 {
                        body = file.readAll();
                        file.close();
                 }
                text += QByteArray("Content-Type: ") + QByteArray("text/xml \r\n");
        }
        else if(tempString.contains(".html"))
        {
                 QFile file(tempString.mid(1));
                 if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                 {
                        body = file.readAll();
                        file.close();
                 }
                text += QByteArray("Content-Type: ") + QByteArray("text/html \r\n");
        }
        else if(tempString.contains(".png"))
        {
                 QFile file(tempString.mid(1));
                 QByteArray dumpcontents;
                 if (file.open(QIODevice::ReadOnly))
                 {
                        dumpcontents = file.readAll();
                        file.close();
                 }
                 body = dumpcontents;

     text += QByteArray("Content-Type: ") + QByteArray("image/png \r\n");
     //text += QByteArray("content-transfer-encoding: ") + QByteArray("base64 \r\n");     

        }
        else
        {
                body = QByteArray("Lorrrummmm Ippsumm Culpa blah blah blah...");
                text += QByteArray("Content-Type: ") + QByteArray("text/html \r\n");
        }

    text += QByteArray("Content-Length: " + QByteArray::number(body.length())  + "\r\n\r\n");

    text += body;
    return text;
}
QStringList XgxPerfServer::FormArgumentListForCmd(QString id)
{
  QStringList tempStringList;
  id = "";

  if((paramList[0]=="0") || (paramList[0]=="1"))//Qt application
  {
    tempStringList << "-qws";
    if(paramList[0]=="1")
    {
	tempStringList << "-display";
	tempStringList << "powervr";
    }
    tempStringList << currCookie; //cookie  
    tempStringList << paramList[5]; //numwidgets
    tempStringList << paramList[7]; //effects
    tempStringList << paramList[8]; //blending
    tempStringList << paramList[9]; //typetexture
    tempStringList << paramList[10]; //text
    tempStringList << paramList[3]; //fps
    tempStringList << paramList[2]; //appid
    tempStringList << paramList[6]; //size widget
    tempStringList << paramList[4]; //num Frames to run
    tempStringList << currDynamicAppName; //App name    
        qDebug() << "params 2,3,4,appname" << paramList[2] << paramList[3] << paramList[4] << currDynamicAppName;
  }
  else if(paramList[0] == "4") //SGXPERF
  {
    tempStringList << paramList[11]; //appid
    tempStringList << paramList[13]; //width
    tempStringList << paramList[14]; //height
    tempStringList << paramList[15]; //rotation
    tempStringList << paramList[16]; //texfmt
    tempStringList << 0; //SVG filename
    tempStringList << paramList[12]; //numobjects        
    tempStringList << paramList[17]; //surfacetype                       
    tempStringList << paramList[4]; //num frames 
    tempStringList << paramList[3]; // fps
    tempStringList << currCookie; //cookie
  }
  return tempStringList;
}

QByteArray XgxPerfServer::formPOSTResponse()
{
    QByteArray text, paramString;
  QStringList tempStringList;
  QString outfilename("/profiledata_");
  QString outfilename1("/profiledata_");
        QString rawfilename("./profiledata_");  
        QString dumpfilename("/dump_");

  currCookie = QTime::currentTime().toString("hhmmsszzz");
  outfilename.append(currCookie);
  outfilename1.append(currCookie);
  dumpfilename.append(currCookie);
  rawfilename.append(currCookie);

          //Run the target application
          QProcess runapp;
          tempStringList = FormArgumentListForCmd(paramList[0]);
#ifdef Q_WS_WIN
          runapp.execute(QString("na2dperf.exe"), tempStringList);
#else
    if((paramList[0] == "0") || (paramList[0]== "1"))//qte
    {
           //runapp.execute(QString("./qt_e"), tempStringList);
           qDebug() << "list command = " << tempStringList;
           runapp.start(QString("./qt_e"), tempStringList);
           runapp.waitForFinished(3*60000);
           if(runapp.error()==false) processErrorMsg = "Application was terminated after 3 minutes. Try reducing # of iterations...";
           else processErrorMsg = "Application completed successfully...";
    }
          else if(paramList[0] == "4") //sgxperf
           runapp.execute(QString("./sgxperf2"), tempStringList);
#endif
          runapp.close();


    QByteArray body =
                QByteArray("<HTML>") +
      QByteArray("<div style= border: blue 2px solid;> \
                        <TABLE HEIGHT=200 WIDTH=500><TR><TD BGCOLOR=#f2f2f2>");
                        
    /* XML */
      if(!currIPAddress.contains("127.0.0.1") && !(currIPAddress.contains("localhost")))
      {
           body +=
                QByteArray("<hr>") + processErrorMsg.toLatin1() + QByteArray("<br><a href=")+QString('"').toLatin1()+
                QByteArray("http://")+
                currIPAddress.toLatin1() + ':' +
    QByteArray(QString("%1").arg(currPort).toLatin1()) +
                QString(outfilename.append(".xml")).toLatin1() +
                QString('"').toLatin1()+
                QByteArray(">View Performance Results(XML)</a>");
    /* HTML */
       body +=
                QByteArray("<hr><a href=")+QString('"').toLatin1()+
                QByteArray("http://")+
                currIPAddress.toLatin1() + ':' +
    QByteArray(QString("%1").arg(currPort).toLatin1()) +
                QString(outfilename1.append(".html")).toLatin1() +
                QString('"').toLatin1()+
                QByteArray(">View Performance Results(Table Form)</a>");                
                /*  dump */
           body +=                
                QByteArray("<hr><br><br><a href=")+
                QString('"').toLatin1()+
                QByteArray("http://")+
                currIPAddress.toLatin1() + ':' +
    QByteArray(QString("%1").arg(currPort).toLatin1()) +
                QString(dumpfilename.append(".png")).toLatin1() +
                QString('"').toLatin1()+
                QByteArray(">View screen shot (PNG)</a>");
        }
        /* Dont need full op on local */
        else
        {
                 QFile file3(rawfilename.append(".txt"));
                 qDebug() << "rawfilename = " << rawfilename;
                 if (file3.open(QIODevice::ReadOnly | QIODevice::Text))
                 {
                        body += file3.readAll();
                        file3.close();
                 } 
                 else qDebug() << "could not open raw file";                 
        }
        body +=
                /* Another test */
                QByteArray("<hr><br><br><a href=")+
                QString('"').toLatin1()+
                QByteArray("http://")+
                currIPAddress.toLatin1() + ':' +
    QByteArray(QString("%1").arg(currPort).toLatin1()) +
                QByteArray("/xgxperf.html")+
                QString('"').toLatin1()+
                QByteArray(">Run another test...</a>") +
                QByteArray("<br><br>") +
    QByteArray("</TD></TR></TABLE></div>") +
                QByteArray("</HTML>\r\n\r\n");



        text += QByteArray("HTTP/1.1 200 OK \r\n");
    text += QByteArray("Content-Type: ") + QByteArray("text/html \r\n")
    + QByteArray("Content-Length: " + QByteArray::number(body.length())  + "\r\n\r\n");

    text += body;
    return text;
}





