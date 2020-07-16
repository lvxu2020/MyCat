TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui
CONFIG += c++11

TARGET = LvXumqtt

INCLUDEPATH += /usr/local/include/

LIBS += -lpthread \
    -L /usr/local/lib/paho-mqtt3c

HEADERS += \
    $$PWD/mqttClinet.h \
    $$PWD/mqttSend.h


SOURCES += \
    $$PWD/mqttClinet.cpp \
    $$PWD/mqttSend.cpp

DESTDIR =/home/lvxu/qt_output/executableProgram/cat/lib

