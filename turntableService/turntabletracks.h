#ifndef TURNTABLETRACKS_H
#define TURNTABLETRACKS_H

#include <unordered_map>
#include <string>
#include <QDir>

class TurntableTracks
{
public:
    TurntableTracks();

    void addTrack(const std::string& key, int32_t value)
    {
        if (value >= 0) {
            deleteTrack(key);
            tracks.insert({key, value});
            saveFile();
        }
    }

    int32_t getTrackPosition(const std::string& track) const
    {
        auto search = tracks.find(track);

        if (search != tracks.end())
            return search->second;

        return -1;
    }

    std::unordered_map<std::string, int32_t> getTracks() const { return tracks; }

    bool loadFile();

    void deleteTrack(const std::string& key)
    {
        tracks.erase(key);
        saveFile();
    }

    void saveFile();

private:
    const std::string configFilePath = QDir(QDir::homePath()).filePath(".turntableSvcCfg").toStdString();
    std::unordered_map<std::string, int32_t> tracks;
};

#endif // TURNTABLETRACKS_H
