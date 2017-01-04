#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Network : public QThread
{
    Q_OBJECT

public:
    //explicit
    Network(QObject *parent = 0);
    ~Network();

    void run() override;
    void connectToHost(const QString &hostName, quint16 port);
    void disconnectFromHost();

    QString HostName() const { return hostName; }
    quint16 Port() const { return port; }

private slots:
    void messageReceived(const QString &received);
    void error(int socketError, const QString &message);

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};

#endif // NETWORK_H
