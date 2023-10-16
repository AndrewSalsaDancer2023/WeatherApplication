#include "settingstore.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QByteArray>
#include <QJsonObject>

const QString geocodingKey = "geokey";
const QString forecastKey = "forecastkey";

void settingStore::readSettings()
{
    QFile file(save_path);
    if(file.exists() && file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &error);
        file.close();
        if(error.error != QJsonParseError::NoError)
           return;

       auto json = doc.object();
       if(json.contains(geocodingKey))
            openCageKey = json.value(geocodingKey).toString();

        //if(object.contains(forecastKey))
        //    weatherForecastKey = object.at(forecastKey).as_string();
       if(json.contains(forecastKey))
            weatherForecastKey = json.value(forecastKey).toString();
    }
}

settingStore::settingStore(const QString& json_path)
    : save_path{json_path}
{
    readSettings();
}
