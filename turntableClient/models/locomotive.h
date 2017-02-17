#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include <sstream>
#include <string>
#include "dccclientnetwork.h"
#include "locomotivefunction.h"

class Locomotive : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(QQmlListProperty<LocomotiveFunction> functionValues READ functionValues NOTIFY functionValuesChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit Locomotive(int id = 0, DccClientNetwork* net = nullptr, QObject *parent = 0);

    int id() const { return m_id; }
    bool direction() const { return m_direction; }
    QQmlListProperty<LocomotiveFunction> functionValues() { return QQmlListProperty<LocomotiveFunction>(this, m_functionValues); }
    int speed() const { return m_speed; }
    DccClientNetwork* network() { return m_network; }


signals:
    void idChanged();
    void directionChanged();
    void functionValuesChanged();
    void speedChanged();

public slots:
    void setId(int value) {
        if (value == m_id) return;

        m_id = value;
        emit idChanged();
    }

    void setDirection(bool value) {
        if (value == m_direction) return;
        m_direction = value;
        emit directionChanged();

        std::ostringstream output;
        output << "LS " << m_id << (m_direction ? " N" : " C") << '\n';
        m_network->sendMessage(output.str());
    }

    void setSpeed(int value) {
        if (value == m_speed || value < 0.0 || value > 126.0)
            return;
        m_speed = value;
        emit speedChanged();

        std::ostringstream output;
        output << "LV " << m_id << " " << value << '\n';
        m_network->sendMessage(output.str());
    }

private:
    bool m_direction;
    int m_id;
    QList<LocomotiveFunction*> m_functionValues;
    DccClientNetwork* m_network;
    int m_speed;
};

#endif // LOCOMOTIVE_H
