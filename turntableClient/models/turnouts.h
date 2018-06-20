#ifndef TURNOUTS_H
#define TURNOUTS_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include <sstream>
#include <string>
#include "dccclientnetwork.h"

class Turnouts: public QObject
{
    public:
        explicit Turnouts(int id = 0, DccClientNetwork* net = nullptr, QObject *parent = 0);

        int id() const { return m_id; }
        DccClientNetwork* network() { return m_network; }
private:
    int m_id;
    DccClientNetwork* m_network;

};
#endif // TURNOUTS_H
