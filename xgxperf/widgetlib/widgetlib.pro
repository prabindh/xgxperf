TEMPLATE = lib
TARGET = widget

SOURCES += widgetlib.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

RESOURCES += widgetlib.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


