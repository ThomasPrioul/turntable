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
    ../turntableClient/circularbuffer.h \
    servicestate.h \
    networkconfig.h \
    turntabletracks.h

linux-rasp-pi2-g++ {
    message($$QMAKESPEC)
    INCLUDEPATH += /home/thomas/raspi/sysroot/usr/include
    LIBS += -L/home/thomas/raspi/sysroot/usr/lib -lwiringPi -lpthread -pthread
    target.files    = turntableservice
    target.path     = /home/pi
}

!linux-rasp-pi2-g++ {
    INCLUDEPATH += test
}

INSTALLS = target
