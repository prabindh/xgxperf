TEMPLATE = lib
TARGET = sewingmachine

SOURCES += sewingmachine.cpp export.cpp

FORMS = mainwindow.ui

HEADERS += ../applicationmanager/common/applicationbase.h

RESOURCES += sewingmachinelib.qrc

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target


