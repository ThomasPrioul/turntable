QT += qml quick

CONFIG += c++11

TARGET = turntableClient


SOURCES += main.cpp \
    turntableapplication.cpp \
    controllers/turntablecontroller.cpp \
    dccclientnetwork.cpp \
    macros.cpp \
    clientsettings.cpp \
    models/locomotive.cpp \
    controllers/lococontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = views

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = views

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    turntableapplication.h \
    ../turntableService/networkconfig.h \
    ../turntableService/circularbuffer.h \
    macros.h \
    controllers/icontroller.h \
    controllers/turntablecontroller.h \
    dccclientnetwork.h \
    models/track.h \
    models/tracksmodel.h \
    clientsettings.h \
    models/locomotive.h \
    controllers/lococontroller.h

linux-rasp-pi2-g++ {
    target.files    = turntableservice
    target.path     = /home/pi
}

!linux-rasp-pi2-g++ {
    #INCLUDEPATH += test
}

INSTALLS = target
