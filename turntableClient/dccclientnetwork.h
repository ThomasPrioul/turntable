#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QtNetwork>
#include <vector>
#include <string>
#include "circularbuffer.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

class DccClientNetwork : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString hostname READ hostname)
    Q_PROPERTY(QString port READ port)

public:
    explicit DccClientNetwork(QObject *parent = 0);
    ~DccClientNetwork();

    QString hostname() const { return m_hostname; }
    quint16 port() const { return m_port; }

    void setHostname(const QString& name) {
        if (name != m_hostname) {
            m_hostname = name;
            emit hostNameChanged();
        }
    }
    void setPort(quint16 port) {
        if (port != m_port) {
            m_port = port;
            emit portChanged();
        }
    }

signals:
    void connected(const QString &hostname, quint16 m_port);
    void disconnected();
    void messageReceived(const std::vector<char> &message);
    void messageSentQString(const QString& msg);

    void hostNameChanged();
    void portChanged();

public slots:
    void connectToHost(const QString &m_hostname, quint16 m_port);
    void disconnectFromHost();
    void sendMessage(const std::string& message);
    void sendMessage(const QString& message) { sendMessage(message.toStdString()); }

private slots:
    void socketConnected();
    void socketDataAvailable();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError error);

private:
    bool m_connected;
    bool m_connecting;
    QString m_hostname;
    quint16 m_port;
    QTcpSocket m_socket;
    CircularBuffer<char> m_readBuffer;
};

#endif // CLIENTNETWORK_H
