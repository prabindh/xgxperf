TEMPLATE = lib
TARGET = automation

QT += svg

SOURCES += automation.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

RESOURCES += automationlib.qrc
target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


