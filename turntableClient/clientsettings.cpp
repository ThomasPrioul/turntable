#include <QFileInfo>
#include <fstream>
#include <iostream>
#include <sstream>
#include "clientsettings.h"

// check if file exists and if yes: Is it really a file and not a directory?
static bool fileExists(const std::string& path) {
    QFileInfo check_file(QString::fromStdString(path));
    return check_file.exists() && check_file.isFile();
}

ClientSettings::ClientSettings(QObject* parent) : QObject(parent), m_serverIP(NetworkConfig::defaultIP)
{
    if (!fileExists(configFilePath)) {
        std::cout << "Configuration file doesn't exist." << '\n'
                  << "Creating configuration file..." << std::endl;

        std::ofstream fs;
        fs.open(configFilePath);
        if (fs.is_open()) {
            fs.close();
            std::cout << "Done." << std::endl;
        }
        else {
            std::cerr << "Could not create configuration file." << std::endl;
        }
    }
}

void ClientSettings::clear()
{
    m_serverIP = std::string(NetworkConfig::defaultIP);
    m_serverPort = NetworkConfig::defaultPort;
    emit serverIPChanged();
    emit serverPortChanged();
}

bool ClientSettings::load()
{
    std::ifstream inputFile;
    std::cout << "loadFile: reading cfg from file" << std::endl;
    inputFile.open(configFilePath);

    if (inputFile.is_open()) {
        std::string line;
        clear();

        if (std::getline(inputFile, line)) {
            std::istringstream lineParser(line);
            std::string ip;
            uint16_t port;

            if (std::getline(lineParser, ip, ':') && lineParser >> port) {
                m_serverIP = ip;
                m_serverPort = port;
                emit serverIPChanged();
                emit serverPortChanged();
            }
            else {
                std::cerr << "Could not read ip and port in line: " << line << '.' << std::endl;
            }
        }

        inputFile.close();
        std::cout << "loadFile : done." << std::endl;
        return true;
    }
    else {
        std::cerr << "loadFile: could not open the configuration file (" << configFilePath << ")." << std::endl;
    }

    return false;
}

bool ClientSettings::save()
{
    std::ofstream outputFile;
    outputFile.open (configFilePath, std::ios::trunc);
    if (outputFile.is_open()) {
        outputFile << m_serverIP << ":" << m_serverPort << std::endl;
        outputFile.close();

        return true;
    }
    else {
        std::cerr << "saveFile: could not open the configuration file (" << configFilePath << ")." << std::endl;
    }

    return false;
}
