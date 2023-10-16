#include "forecastmodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QDebug>
ForecastModel::ForecastModel()
{
    restorePlaces();
}

void ForecastModel::setCurrentForecast(const GeoData& geocoord, const CurrentWeatherForecast& forecast)
{
   // forecastModel[geocoord] = ForecastData();
    forecastModel[geocoord].currentForecast = forecast;
}

void ForecastModel::setFiveDayForecast(const GeoData& geocoord, const forecastArray& forecast)
{
    forecastModel[geocoord].fiveDayForecast = forecast;
}

std::optional<CurrentWeatherForecast> ForecastModel::getCurrentForecast(const GeoData& geocoord)
{
    auto itFind = forecastModel.find(geocoord);
    if(itFind != forecastModel.end())
        return itFind->second.currentForecast;

    return std::nullopt;
}

std::optional<forecastArray> ForecastModel::getFiveDayForecast(const GeoData& geocoord)
{
    auto itFind = forecastModel.find(geocoord);
    if(itFind != forecastModel.end())
        return itFind->second.fiveDayForecast;

    return std::nullopt;
}

void ForecastModel::savePlaces()
{
    QJsonArray array;
    for(auto it = forecastModel.begin(); it != forecastModel.end(); ++it)
    {
        QJsonObject jobject;
        jobject["placeName"] = it->first.placeName;
        jobject["lat"] = it->first.coord.lat;
        jobject["lon"] = it->first.coord.lon;

        array.push_back(jobject);
    }

    QJsonDocument doc{array};
    QString content{doc.toJson()};

    QSettings settings{"DSS", "WeatherApp"};
    settings.setValue("locations", content);
}

void ForecastModel::restorePlaces()
{
    QSettings settings{"DSS", "WeatherApp"};
    QString content = settings.value("locations").toString();
    qDebug() << content;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    if(!doc.isArray())
        return;

    QJsonArray arr = doc.array();
    for(int i = 0; i < arr.count(); ++i)
    {
        GeoData data;
        QJsonObject jobject = arr.at(i).toObject();
        data.placeName = jobject["placeName"].toString();
        data.coord.lat = jobject["lat"].toDouble();
        data.coord.lon = jobject["lon"].toDouble();

        auto itFind = forecastModel.find(data);
        if(itFind != forecastModel.end())
           continue;

        forecastModel[data] = ForecastData();

    }
}

bool ForecastModel::locationAlreadyStored(const GeoData& location)
{
    auto itFind = forecastModel.find(location);
    return (itFind != forecastModel.end());
}

void ForecastModel::deleteStoredLocation(const GeoData& location)
{
    auto itFind = forecastModel.find(location);
    if(itFind == forecastModel.end())
        return;

    forecastModel.erase(itFind);
}

std::vector<GeoData> ForecastModel::getPlaces()
{
    std::vector<GeoData> res;

    for(const auto& item: forecastModel)
        res.push_back(item.first);

    std::sort(res.begin(), res.end(),[](const GeoData& data1, const GeoData& data2){
       return data1.placeName < data2.placeName;
    });

    return res;
}
