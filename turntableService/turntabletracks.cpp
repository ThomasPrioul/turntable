#include <iostream>
#include <fstream>
#include <sstream>
#include <QFileInfo>

#include "turntabletracks.h"

// check if file exists and if yes: Is it really a file and not a directory?
static bool fileExists(const std::string& path) {
    QFileInfo check_file(QString::fromStdString(path));
    return check_file.exists() && check_file.isFile();
}

TurntableTracks::TurntableTracks()
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

bool TurntableTracks::loadFile()
{
    std::ifstream inputFile;
    std::cout << "loadFile: reading tracks information from configuration file..." << std::endl;
    inputFile.open(configFilePath);
    if (inputFile.is_open()) {
        tracks.clear();
        std::string line;

        while (std::getline(inputFile, line)) {
            std::istringstream lineParser(line);
            std::string track;
            int32_t position;
            bool polarity;

            if (std::getline(lineParser, track, ';') && lineParser >> position && lineParser.ignore(10, ';') && lineParser >> polarity) {
                tracks.insert({track, { position, polarity }});
                std::cout << "Track: " << track << ", pos: " << position << std::endl;
            }
            else {
                std::cerr << "Could not read trackname and position in line: " << line << '.' << std::endl;
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

void TurntableTracks::saveFile()
{
    std::ofstream outputFile;
    outputFile.open (configFilePath, std::ios::trunc);
    if (outputFile.is_open()) {
        auto i = tracks.begin();

        while (i != tracks.end()) {
            outputFile << i->first << ';' << i->second.position << ';' << i->second.polarity << '\n';
            std::cout << i->first  << ';' << i->second.position << ';' << i->second.polarity << std::endl;
            ++i;
        }

        outputFile.close();
    }
    else {
        std::cerr << "saveFile: could not open the configuration file (" << configFilePath << ")." << std::endl;
    }
}
