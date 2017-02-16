#ifndef TURNTABLETRACKS_H
#define TURNTABLETRACKS_H

#include <unordered_map>
#include <string>
#include <QDir>

struct TrackInfo {
    int32_t position;
    bool polarity;
};

class TurntableTracks
{
public:
    TurntableTracks();

    void addTrack(const std::string& key, int32_t value, bool polarity)
    {
        if (value >= 0) {
            deleteTrack(key);
            TrackInfo info;
            info.position = value;
            info.polarity = polarity;
            tracks.insert({key, info});
            saveFile();
        }
    }

    int32_t getTrackPosition(const std::string& track) const
    {
        auto search = tracks.find(track);

        if (search != tracks.end())
            return search->second.position;

        return -1;
    }

    TrackInfo getTrackInfo(const std::string& track) const
    {
        auto search = tracks.find(track);

        if (search != tracks.end())
            return search->second;

        return TrackInfo();
    }

    std::unordered_map<std::string, TrackInfo> getTracks() const { return tracks; }

    bool loadFile();

    void deleteTrack(const std::string& key)
    {
        tracks.erase(key);
        saveFile();
    }

    void saveFile();

private:
    const std::string configFilePath = QDir(QDir::homePath()).filePath(".turntableSvcCfg").toStdString();
    std::unordered_map<std::string, TrackInfo> tracks;
};

#endif // TURNTABLETRACKS_H
