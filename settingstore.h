#ifndef SETTINGSTORE_H
#define SETTINGSTORE_H

#include <memory>
#include <QString>

const QString file_path = "../config/settings.json";
//namespace json = boost::json;

class settingStore
{
public:
    QString getGeocodingKey() { return openCageKey;}
    QString getWeatherForecastKey() { return weatherForecastKey; }
    void readSettings();
   // void serializeSettings(){}
    static settingStore& getInstance()
    {
        static settingStore instance{"../config/settings.json"};
        return instance;
    }
private:

    settingStore() = delete;
    settingStore(const settingStore&) = delete;
    settingStore& operator=(settingStore &) = delete;

    explicit settingStore(const QString& json_path);
    //void readSettings(const json::object& object);
    const QString save_path;
    QString openCageKey;
    QString weatherForecastKey;


};

#endif // SETTINGSTORE_H
