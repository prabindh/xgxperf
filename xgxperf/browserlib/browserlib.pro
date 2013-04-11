TEMPLATE = lib

QT += webkit network

TARGET = browser

SOURCES += browserlib.cpp export.cpp

HEADERS += browserlib.h ../applicationmanager/common/applicationbase.h

RESOURCES += browserlib.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


