#ifndef LOCOCONTROLLER_H
#define LOCOCONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
#include "icontroller.h"
#include "models/locomotive.h"

class LocoController : public QObject, IController
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Locomotive> locomotives READ locomotives NOTIFY locomotivesChanged)
    Q_INTERFACES(IController)

public:
    explicit LocoController(TurntableApplication* appRef = 0, QObject *parent = 0);

    QQmlListProperty<Locomotive> locomotives() {
        return QQmlListProperty<Locomotive>(this, m_locomotives);
    }

signals:
    void locomotivesChanged();

public slots:
    void addLocomotive() {

    }

    void deleteLocomotive() {

    }

    void clear() {
        m_locomotives.clear();
        emit locomotivesChanged();
    }

    void messageReceived(const std::string& msg);

private:
    QList<Locomotive*> m_locomotives;
};

#endif // LOCOCONTROLLER_H
