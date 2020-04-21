TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui

HEADERS += \
    $$PWD/base.h \
    singleton.h

SOURCES += \
    $$PWD/base.cpp

DESTDIR = ~/myCat/executableProgram/Cat/lib
