#ifndef MACROS_H
#define MACROS_H
//#include <QQmlEngine>
#include <string>

bool startsWith(const std::string& longStr, const std::string& shortStr);

//#define QML_REGISTER(a) static int unused_val = qmlRegisterType<a>("turntable.client", 1, 0, #a)

#endif // MACROS_H
