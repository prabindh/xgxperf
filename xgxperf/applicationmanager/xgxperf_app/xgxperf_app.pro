
SOURCES += main.cpp \
    applicationmanager.cpp
    
HEADERS += applicationmanager.h \
    ../common/applicationbase.h

RESOURCES += xgxperf_app.qrc

target.path=$$[QT_INSTALL_BINS]
INSTALLS += target

QT += widgets

