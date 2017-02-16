#ifndef LOCOMOTIVEFUNCTION_H
#define LOCOMOTIVEFUNCTION_H

#include <QObject>
#include <sstream>
#include <string>

class Locomotive;

class LocomotiveFunction : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(bool functionValue READ functionValue WRITE setFunctionValue NOTIFY functionValueChanged)

public:
    explicit LocomotiveFunction(int id = 0, bool funcVal = false, Locomotive* loco = nullptr, QObject* parent = 0);

    int id() const { return m_id; }
    bool functionValue() const { return m_functionValue; }

signals:
    void idChanged();
    void functionValueChanged();

public slots:
    void setFunctionValue(bool value);
private:
    int m_id;
    Locomotive* m_loco;
    bool m_functionValue;
};

#endif // LOCOMOTIVEFUNCTION_H
