TEMPLATE = lib
TARGET = xgxperftemplate 

SOURCES += xgxperftemplate.cpp export.cpp

HEADERS += ../applicationmanager/common/applicationbase.h

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


