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
    Q_PROPERTY(bool powerActive READ powerActive NOTIFY powerActiveChanged)
    Q_INTERFACES(IController)

public:
    explicit LocoController(TurntableApplication* appRef = 0, QObject *parent = 0);

    QQmlListProperty<Locomotive> locomotives() {
        return QQmlListProperty<Locomotive>(this, m_locomotives);
    }

    bool powerActive() const { return m_powerActive; }

signals:
    void locomotivesChanged();
    void powerActiveChanged();

public slots:

    void addLocomotive() {

    }

    void deleteLocomotive() {

    }

    void clear() {
        m_locomotives.clear();
        emit locomotivesChanged();
    }

    void powerOn();
    void powerOff();

    void messageReceived(const std::string& msg);

    void refresh(int id);
private:
    QList<Locomotive*> m_locomotives;
    bool m_powerActive;
    Locomotive *findLoco(int id);
};

#endif // LOCOCONTROLLER_H
