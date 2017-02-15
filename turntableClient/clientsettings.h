#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <string>
#include <stdint.h>
#include <QDir>
#include <QObject>
#include "../turntableService/networkconfig.h"

class ClientSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString serverIP READ serverIP WRITE setServerIP NOTIFY serverIPChanged)
    Q_PROPERTY(quint16 serverPort READ serverPort WRITE setServerPort NOTIFY serverPortChanged)

public:
    explicit ClientSettings(QObject* parent = 0);

public slots:
    void clear();
    bool load();
    bool save();

public:
    QString serverIP() { return QString::fromStdString(m_serverIP); }
    quint16 serverPort() const { return m_serverPort; }
    void setServerIP(const QString& value) {
        std::string stdVal = value.toStdString();
        if (m_serverIP == stdVal)
            return;
        m_serverIP = stdVal;
        emit serverIPChanged();
    }
    void setServerPort(quint16 value) {
        if (m_serverPort == value)
            return;
        m_serverIP = value;
        emit serverPortChanged();
    }

signals:
    void serverIPChanged();
    void serverPortChanged();

private:
    std::string m_serverIP;
    uint16_t m_serverPort = NetworkConfig::defaultPort;
    const std::string configFilePath = QDir(QDir::homePath()).filePath(".turntableClientCfg").toStdString();
};

#endif // CLIENTSETTINGS_H
