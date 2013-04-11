/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_3;
    QPushButton *playBackImgpushButton_2;
    QPushButton *CameraViewImg1pushButton;
    QPushButton *CameraViewImg2pushButton;
    QPushButton *CameraViewImg4pushButton;
    QPushButton *CameraViewImg5pushButton;
    QPushButton *vsmImgpushButton;
    QPushButton *addEditCameraImgpushButton;
    QPushButton *displaypushButton;
    QPushButton *volumeImgpushButton;
    QPushButton *settingImgpushButton;
    QPushButton *pushButton_10;
    QPushButton *pushButton_7;
    QPushButton *ResetpushButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gl_gridLayout;
    QPushButton *camFlowpushButton;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QPushButton *playBackImgpushButton_3;
    QGroupBox *groupBox_4;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_18;
    QPushButton *logopushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QStatusBar *statusBar;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QFont font;
        font.setPointSize(8);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/vs/ti_icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 800, 581));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 800, 581));
        playBackImgpushButton_2 = new QPushButton(groupBox_3);
        playBackImgpushButton_2->setObjectName(QStringLiteral("playBackImgpushButton_2"));
        playBackImgpushButton_2->setEnabled(true);
        playBackImgpushButton_2->setGeometry(QRect(40, 20, 42, 28));
        playBackImgpushButton_2->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/vs/videocamera_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        playBackImgpushButton_2->setIcon(icon1);
        playBackImgpushButton_2->setDefault(false);
        playBackImgpushButton_2->setFlat(false);
        playBackImgpushButton_2->setProperty("fixedSize", QVariant(QSize(42, 28)));
        CameraViewImg1pushButton = new QPushButton(groupBox_3);
        CameraViewImg1pushButton->setObjectName(QStringLiteral("CameraViewImg1pushButton"));
        CameraViewImg1pushButton->setGeometry(QRect(180, 20, 28, 28));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CameraViewImg1pushButton->sizePolicy().hasHeightForWidth());
        CameraViewImg1pushButton->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/vs/single-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        CameraViewImg1pushButton->setIcon(icon2);
        CameraViewImg1pushButton->setFlat(false);
        CameraViewImg1pushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        CameraViewImg2pushButton = new QPushButton(groupBox_3);
        CameraViewImg2pushButton->setObjectName(QStringLiteral("CameraViewImg2pushButton"));
        CameraViewImg2pushButton->setGeometry(QRect(220, 20, 28, 28));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/vs/four-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        CameraViewImg2pushButton->setIcon(icon3);
        CameraViewImg2pushButton->setFlat(false);
        CameraViewImg2pushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        CameraViewImg4pushButton = new QPushButton(groupBox_3);
        CameraViewImg4pushButton->setObjectName(QStringLiteral("CameraViewImg4pushButton"));
        CameraViewImg4pushButton->setEnabled(true);
        CameraViewImg4pushButton->setGeometry(QRect(260, 20, 28, 28));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/vs/nine-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        CameraViewImg4pushButton->setIcon(icon4);
        CameraViewImg4pushButton->setFlat(false);
        CameraViewImg4pushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        CameraViewImg5pushButton = new QPushButton(groupBox_3);
        CameraViewImg5pushButton->setObjectName(QStringLiteral("CameraViewImg5pushButton"));
        CameraViewImg5pushButton->setEnabled(true);
        CameraViewImg5pushButton->setGeometry(QRect(300, 20, 28, 28));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/vs/sixteen-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        CameraViewImg5pushButton->setIcon(icon5);
        CameraViewImg5pushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        vsmImgpushButton = new QPushButton(groupBox_3);
        vsmImgpushButton->setObjectName(QStringLiteral("vsmImgpushButton"));
        vsmImgpushButton->setEnabled(true);
        vsmImgpushButton->setGeometry(QRect(430, 20, 28, 28));
        vsmImgpushButton->setIcon(icon4);
        vsmImgpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        addEditCameraImgpushButton = new QPushButton(groupBox_3);
        addEditCameraImgpushButton->setObjectName(QStringLiteral("addEditCameraImgpushButton"));
        addEditCameraImgpushButton->setEnabled(true);
        addEditCameraImgpushButton->setGeometry(QRect(470, 20, 28, 28));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/vs/camera-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        addEditCameraImgpushButton->setIcon(icon6);
        addEditCameraImgpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        displaypushButton = new QPushButton(groupBox_3);
        displaypushButton->setObjectName(QStringLiteral("displaypushButton"));
        displaypushButton->setEnabled(true);
        displaypushButton->setGeometry(QRect(550, 20, 28, 28));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/vs/expand-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        displaypushButton->setIcon(icon7);
        displaypushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        volumeImgpushButton = new QPushButton(groupBox_3);
        volumeImgpushButton->setObjectName(QStringLiteral("volumeImgpushButton"));
        volumeImgpushButton->setEnabled(true);
        volumeImgpushButton->setGeometry(QRect(600, 20, 28, 28));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/vs/speaker-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        volumeImgpushButton->setIcon(icon8);
        volumeImgpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        settingImgpushButton = new QPushButton(groupBox_3);
        settingImgpushButton->setObjectName(QStringLiteral("settingImgpushButton"));
        settingImgpushButton->setEnabled(true);
        settingImgpushButton->setGeometry(QRect(640, 20, 28, 28));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/vs/options-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        settingImgpushButton->setIcon(icon9);
        settingImgpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setEnabled(true);
        pushButton_10->setGeometry(QRect(680, 20, 28, 28));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/vs/computer-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_10->setIcon(icon10);
        pushButton_10->setProperty("fixedSize", QVariant(QSize(28, 28)));
        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setEnabled(true);
        pushButton_7->setGeometry(QRect(720, 20, 28, 28));
        pushButton_7->setFont(font);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/vs/help-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon11);
        pushButton_7->setProperty("fixedSize", QVariant(QSize(28, 28)));
        ResetpushButton = new QPushButton(groupBox_3);
        ResetpushButton->setObjectName(QStringLiteral("ResetpushButton"));
        ResetpushButton->setEnabled(true);
        ResetpushButton->setGeometry(QRect(760, 20, 28, 28));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/vs/exit-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        ResetpushButton->setIcon(icon12);
        ResetpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(697, 65, 101, 461));
        gl_gridLayout = new QGridLayout(gridLayoutWidget);
        gl_gridLayout->setSpacing(6);
        gl_gridLayout->setContentsMargins(11, 11, 11, 11);
        gl_gridLayout->setObjectName(QStringLiteral("gl_gridLayout"));
        gl_gridLayout->setContentsMargins(0, 0, 0, 0);
        camFlowpushButton = new QPushButton(groupBox_3);
        camFlowpushButton->setObjectName(QStringLiteral("camFlowpushButton"));
        camFlowpushButton->setGeometry(QRect(390, 20, 28, 28));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/vs/cam-flow_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        camFlowpushButton->setIcon(icon13);
        camFlowpushButton->setProperty("fixedSize", QVariant(QSize(28, 28)));
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setEnabled(true);
        pushButton_9->setGeometry(QRect(340, 20, 28, 28));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/vs/cascade-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_9->setIcon(icon14);
        pushButton_9->setProperty("fixedSize", QVariant(QSize(28, 28)));
        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setEnabled(true);
        pushButton_8->setGeometry(QRect(510, 20, 28, 28));
        pushButton_8->setFont(font);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/images/vs/play-button_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon15);
        pushButton_8->setProperty("fixedSize", QVariant(QSize(28, 28)));
        playBackImgpushButton_3 = new QPushButton(groupBox_3);
        playBackImgpushButton_3->setObjectName(QStringLiteral("playBackImgpushButton_3"));
        playBackImgpushButton_3->setEnabled(true);
        playBackImgpushButton_3->setGeometry(QRect(80, 20, 42, 28));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/vs/moviereel_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        playBackImgpushButton_3->setIcon(icon16);
        playBackImgpushButton_3->setFlat(false);
        playBackImgpushButton_3->setProperty("fixedSize", QVariant(QSize(42, 28)));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(5, 60, 171, 481));
        treeWidget = new QTreeWidget(groupBox_4);
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtreewidgetitem->setFont(0, font1);
        __qtreewidgetitem->setBackground(0, QColor(207, 204, 212));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setFont(0, font2);
        __qtreewidgetitem1->setBackground(0, brush);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem3->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem4->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem5->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem6->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem7->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem8->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem9->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem10->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem11->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem12->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem13->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem14->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem15->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem16->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem17->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem17);
        __qtreewidgetitem18->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem17);
        __qtreewidgetitem19->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem17);
        __qtreewidgetitem20->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem17);
        __qtreewidgetitem21->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem22 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem22->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem23 = new QTreeWidgetItem(__qtreewidgetitem22);
        __qtreewidgetitem23->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem24 = new QTreeWidgetItem(__qtreewidgetitem22);
        __qtreewidgetitem24->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem25 = new QTreeWidgetItem(__qtreewidgetitem22);
        __qtreewidgetitem25->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem26 = new QTreeWidgetItem(__qtreewidgetitem22);
        __qtreewidgetitem26->setFont(0, font2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 10, 151, 201));
        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 230, 151, 131));
        groupBox->setFont(font1);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(true);
        pushButton_2->setGeometry(QRect(85, 20, 64, 32));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_2->setFont(font3);
        pushButton_2->setProperty("fixedSize", QVariant(QSize(96, 64)));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(true);
        pushButton_3->setGeometry(QRect(85, 60, 64, 32));
        pushButton_3->setFont(font3);
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setEnabled(true);
        pushButton_4->setGeometry(QRect(84, 98, 64, 32));
        pushButton_4->setFont(font3);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setGeometry(QRect(0, 30, 82, 82));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/images/vs/button_circle.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon17);
        pushButton->setProperty("fixedSize", QVariant(QSize(82, 82)));
        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 370, 151, 51));
        groupBox_2->setFont(font1);
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setEnabled(true);
        pushButton_5->setGeometry(QRect(0, 20, 24, 24));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/images/vs/reverse-playbackbutton_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon18);
        pushButton_5->setProperty("fixedSize", QVariant(QSize(24, 24)));
        pushButton_14 = new QPushButton(groupBox_2);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setEnabled(true);
        pushButton_14->setGeometry(QRect(30, 20, 24, 24));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/images/vs/stop-playbackbutton_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_14->setIcon(icon19);
        pushButton_14->setProperty("fixedSize", QVariant(QSize(24, 24)));
        pushButton_15 = new QPushButton(groupBox_2);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setEnabled(true);
        pushButton_15->setGeometry(QRect(60, 20, 24, 24));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/images/vs/pause-playbackbutton_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_15->setIcon(icon20);
        pushButton_15->setProperty("fixedSize", QVariant(QSize(24, 24)));
        pushButton_16 = new QPushButton(groupBox_2);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setEnabled(true);
        pushButton_16->setGeometry(QRect(90, 21, 24, 24));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/images/vs/play-playbackbutton_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_16->setIcon(icon21);
        pushButton_16->setProperty("fixedSize", QVariant(QSize(24, 24)));
        pushButton_18 = new QPushButton(groupBox_2);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setEnabled(true);
        pushButton_18->setGeometry(QRect(120, 20, 24, 24));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/images/vs/forward-playbackbutton_03.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_18->setIcon(icon22);
        pushButton_18->setProperty("fixedSize", QVariant(QSize(24, 24)));
        logopushButton = new QPushButton(groupBox_4);
        logopushButton->setObjectName(QStringLiteral("logopushButton"));
        logopushButton->setGeometry(QRect(10, 430, 151, 41));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/images/vs/logo.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        logopushButton->setIcon(icon23);
        logopushButton->setProperty("fixedSize", QVariant(QSize(150, 200)));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 60, 221, 221));
        label->setAutoFillBackground(false);
        label->setFrameShape(QFrame::Box);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/vs/sun1.jpg")));
        label->setScaledContents(true);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 60, 211, 221));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/vs/sun2.jpg")));
        label_2->setScaledContents(true);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(200, 290, 221, 241));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/images/vs/sun3.jpg")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(440, 290, 211, 241));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/vs/sun1.jpg")));
        label_4->setScaledContents(true);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 0, 3, 18));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "      Hybrid Security Digital Video Decoder Demo", 0));
        groupBox_3->setStyleSheet(QApplication::translate("MainWindow", "background-image: url(:/images/vs/background_03.gif);", 0));
        groupBox_3->setTitle(QString());
        playBackImgpushButton_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        CameraViewImg1pushButton->setToolTip(QApplication::translate("MainWindow", "Layout 1x1", 0));
#endif // QT_NO_TOOLTIP
        CameraViewImg1pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        CameraViewImg2pushButton->setToolTip(QApplication::translate("MainWindow", "Layout 2x2", 0));
#endif // QT_NO_TOOLTIP
        CameraViewImg2pushButton->setText(QString());
        CameraViewImg4pushButton->setText(QString());
        CameraViewImg5pushButton->setText(QString());
        vsmImgpushButton->setText(QString());
        addEditCameraImgpushButton->setText(QString());
        displaypushButton->setText(QString());
        volumeImgpushButton->setText(QString());
        settingImgpushButton->setText(QString());
        pushButton_10->setText(QString());
        pushButton_7->setText(QString());
        ResetpushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        camFlowpushButton->setToolTip(QApplication::translate("MainWindow", "Camera Flow", 0));
#endif // QT_NO_TOOLTIP
        camFlowpushButton->setText(QString());
        pushButton_9->setText(QString());
        pushButton_8->setText(QString());
        playBackImgpushButton_3->setText(QString());
        groupBox_4->setStyleSheet(QApplication::translate("MainWindow", "background-image: url(:/images/vs/background2_03.gif);", 0));
        groupBox_4->setTitle(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "System Controls", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Camera Tree ", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Lobby", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "Cam 1", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "Cam 2", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem2->child(2);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "Cam 3", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem2->child(3);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "Cam 4", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "Main Hall", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem7->child(0);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainWindow", "Cam 5", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem7->child(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainWindow", "Cam 6", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem7->child(2);
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "Cam 7", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem7->child(3);
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainWindow", "Cam 8", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainWindow", "Garage", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "Cam 9", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainWindow", "Cam 10", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem12->child(2);
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainWindow", "Cam 11", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem12->child(3);
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "Cam 12", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainWindow", "Plaza", 0));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem17->child(0);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainWindow", "Cam 13", 0));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem17->child(1);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainWindow", "Cam 14", 0));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem17->child(2);
        ___qtreewidgetitem20->setText(0, QApplication::translate("MainWindow", "Cam 15", 0));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem17->child(3);
        ___qtreewidgetitem21->setText(0, QApplication::translate("MainWindow", "Cam 16", 0));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem22->setText(0, QApplication::translate("MainWindow", "Tables", 0));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem22->child(0);
        ___qtreewidgetitem23->setText(0, QApplication::translate("MainWindow", "Cam 17", 0));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem22->child(1);
        ___qtreewidgetitem24->setText(0, QApplication::translate("MainWindow", "Cam 18", 0));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem22->child(2);
        ___qtreewidgetitem25->setText(0, QApplication::translate("MainWindow", "Cam 19", 0));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem22->child(3);
        ___qtreewidgetitem26->setText(0, QApplication::translate("MainWindow", "Cam 20", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("MainWindow", "Camera Controls", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Image", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Codec", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Analytics", 0));
        pushButton->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Playback Controls", 0));
        pushButton_5->setText(QString());
        pushButton_14->setText(QString());
        pushButton_15->setText(QString());
        pushButton_16->setText(QString());
        pushButton_18->setText(QString());
        logopushButton->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
