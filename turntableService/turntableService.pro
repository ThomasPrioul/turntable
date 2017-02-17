QT += core network
QT -= gui
CONFIG += c++11
TARGET = turntableService

CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += main.cpp \
    turntableservice.cpp \
    turntablemotor.cpp \
    turntablenetwork.cpp \
    turntabletracks.cpp

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -pthread

HEADERS += \
    turntableservice.h \
    turntablemotor.h \
    turntablenetwork.h \
    networkconfig.h \
    turntabletracks.h \
    circularbuffer.h

linux-rasp-pi2-g++ {
    QT += concurrent
    LIBS += -lwiringPi
    DEFINES += RPI_FIX
    target.path     = /home/pi
}

!linux-rasp-pi2-g++ {
    INCLUDEPATH += test
}

INSTALLS = target
