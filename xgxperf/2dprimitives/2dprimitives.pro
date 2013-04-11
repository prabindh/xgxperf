TEMPLATE = lib
TARGET = 2dprimitives 

QT += widgets

SOURCES += 2dprimitives.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


