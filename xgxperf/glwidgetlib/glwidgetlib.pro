TEMPLATE = lib
TARGET = glwidget
QT += opengl

SOURCES += glwidgetlib.cpp export.cpp 

HEADERS += ../applicationmanager/common/applicationbase.h
    
RESOURCES += glwidgetlib.qrc    
   

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target

 
