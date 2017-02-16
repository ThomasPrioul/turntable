#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>

class LocomotiveFunction : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(bool functionValue READ functionValue WRITE setFunctionValue NOTIFY functionValueChanged)

public:
    explicit LocomotiveFunction(int id = 0, bool funcVal = false, QObject* parent = 0) : QObject(parent), m_id(id), m_functionValue(funcVal) {}

    int id() const { return m_id; }
    bool functionValue() const { return m_functionValue; }

signals:
    void idChanged();
    void functionValueChanged();

public slots:
    void setFunctionValue(bool value) {
        if (value == m_functionValue) return;
        m_functionValue = value;
        emit functionValueChanged();
    }

private:
    int m_id;
    bool m_functionValue;
};

class Locomotive : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(bool direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(QQmlListProperty<LocomotiveFunction> functionValues READ functionValues NOTIFY functionValuesChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit Locomotive(int id = 0, QObject *parent = 0);

    int id() const { return m_id; }
    bool direction() const { return m_direction; }
    QQmlListProperty<LocomotiveFunction> functionValues() { return QQmlListProperty<LocomotiveFunction>(this, m_functionValues); }
    int speed() const { return m_speed; }

signals:
    void idChanged();
    void directionChanged();
    void functionValuesChanged();
    void speedChanged();

public slots:
    void setDirection(bool value) {
        if (value == m_direction) return;
        m_direction = value;
        emit directionChanged();
    }
    void setSpeed(int value) {
        if (value == m_speed || value < 0.0 || value > 126.0)
            return;
        m_speed = value;
        emit speedChanged();
    }

private:
    int m_id;
    bool m_direction;
    int m_speed;
    QList<LocomotiveFunction*> m_functionValues;
};

#endif // LOCOMOTIVE_H
