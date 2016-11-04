#ifndef HELPERS_H
#define HELPERS_H

#include <QObject>

class Helpers : public QObject
{
    Q_OBJECT
public:
    static int const EXIT_CODE_REBOOT;

    explicit Helpers(QObject *parent = 0);

    Q_INVOKABLE
    void restartApp();

    Q_INVOKABLE
    void syncSettings();

signals:

public slots:

};

#endif // HELPERS_H
