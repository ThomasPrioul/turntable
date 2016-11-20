TEMPLATE = app
TARGET = protoIHM_PFE
QT += core network quick quickcontrols2 # qml

CONFIG += c++11

SOURCES += main.cpp \
    helpers.cpp \
    clientnetworking.cpp

RESOURCES += \
    IHM.qrc

OTHER_FILES += \
    main.qml \
    views/*.qml \
    views/dialogs/*.qml \
    views/pages/*.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    helpers.h \
    clientnetworking.h

DISTFILES +=
