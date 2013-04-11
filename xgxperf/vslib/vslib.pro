QT += widgets

TEMPLATE = lib
SOURCES = vslib.cpp export.cpp
HEADERS = ../applicationmanager/common/applicationbase.h vslib.h
FORMS = mainwindow.ui
RESOURCES = resource.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


