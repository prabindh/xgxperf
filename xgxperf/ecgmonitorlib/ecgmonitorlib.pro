TEMPLATE = lib
TARGET = ecgmonitor 

SOURCES += ecgmonitor.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

RESOURCES += ecgmonitorlib.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


