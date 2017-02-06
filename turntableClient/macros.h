#ifndef MACROS_H
#define MACROS_H
#include <QQmlEngine>

#define QML_REGISTER(a) static int unused_val = qmlRegisterType<a>("turntable.client", 1, 0, #a)

#endif // MACROS_H
