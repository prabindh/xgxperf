HEADERS       = xgxperfserver.h
SOURCES       = xgxperfserver.cpp \
                main.cpp
QT           += network widgets

target.path=$$[QT_INSTALL_BINS]
INSTALLS += target


