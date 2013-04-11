TEMPLATE = lib
TARGET = autoscreen

SOURCES += autoscreen.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

RESOURCES += autoscreenlib.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


