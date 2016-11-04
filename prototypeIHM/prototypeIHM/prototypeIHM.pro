TEMPLATE = app
TARGET = protoIHM_PFE
QT += quick quickcontrols2 # qml

CONFIG += c++11

SOURCES += main.cpp \
    helpers.cpp

RESOURCES += \
    IHM.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    helpers.h
