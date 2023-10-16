#include <string>
#include "geocoder.h"
#include <algorithm>
#include <boost/json/src.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
namespace json = boost::json;

const QString geoJsonRoot = "results";
const QString placeComponents = "components";
const QString placeConfidense = "confidence";
const QString placeGeometry = "geometry";
const QString placeLat = "lat";
const QString placeLon = "lng";
const QString weatherLon = "lon";

const QString city = "city";
const QString continent = "continent";
const QString country = "country";
const QString region = "region";
const QString formatted = "formatted";

const QString  sysAnchor = "sys";
const QString  sunriseAnchor = "sunrise";
const QString  sunsetAnchor = "sunset";

const QString  coordAnchor = "coord";
const QString  weatherAnchor = "weather";
const QString  descrAnchor = "description";
const QString  mainAnchor = "main";
const QString  dtAnchor = "dt";
const QString  nameAnchor = "name";

const QString  tempAnchor = "temp";
const QString  tempMinAnchor = "temp_min";
const QString  tempMaxAnchor = "temp_max";
const QString  pressureAnchor = "pressure";
const QString  humidityAnchor = "humidity";
const QString  visibilityAnchor = "visibility";
const QString  windAnchor = "wind";
const QString  windSpeedAnchor = "speed";
const QString  iconAnchor = "icon";

const QString dateFormattedAnchor = "dt_txt";
const QString forecastArrayAnchor = "list";
const QString messageAnchor = "message";

void fillWeatherTagData(const QJsonObject& forecastObject, CurrentWeatherForecast& data)
{
    if(forecastObject.contains(descrAnchor))
       data.description = forecastObject.value(descrAnchor).toString();

    if(forecastObject.contains(iconAnchor))
       data.icon = forecastObject.value(iconAnchor).toString();
}

void fillMainTagData(const QJsonObject& mainObj, CurrentWeatherForecast& data)
{
    if(mainObj.contains(tempAnchor))
       data.temperCurrent = static_cast<int>(mainObj.value(tempAnchor).toDouble());

    if(mainObj.contains(tempMinAnchor))
       data.temperMin = static_cast<int>(mainObj.value(tempMinAnchor).toDouble());

    if(mainObj.contains(tempMaxAnchor))
       data.temperMax = static_cast<int>(mainObj.value(tempMaxAnchor).toDouble());

    if(mainObj.contains(pressureAnchor))
       data.pressure = mainObj.value(pressureAnchor).toInt();

    if(mainObj.contains(humidityAnchor))
       data.humidity = mainObj.value(humidityAnchor).toInt();
}

void fillVisibilityData(const QJsonObject& root_object, CurrentWeatherForecast& data)
{
    if(root_object.contains(visibilityAnchor))
       data.visibility = root_object.value(visibilityAnchor).toInt();
}

void fillWindSpeedData(const QJsonObject& root_object, CurrentWeatherForecast& data)
{
    if(!root_object.contains(windAnchor))
        return;

    auto windObj = root_object.value(windAnchor).toObject();
    if(windObj.contains(windSpeedAnchor))
        data.windSpeed = windObj.value(windSpeedAnchor).toDouble();
}

void fillForecastWithDate(const QJsonObject& root_object, threeHoursWeatherForecast& data)
{
    if(root_object.contains(dateFormattedAnchor))
       data.forecastTimeString = root_object.value(dateFormattedAnchor).toString();
}

coordinates ParseCoordObject(const QJsonObject& geometry, const QString& latTag, const QString& lonTag)
{
    coordinates coord;
//    QString str1, str11;
    if(geometry.contains(latTag))
    {
//        auto var = geometry.value(latTag).toVariant();
//        str1 = var.toString();
        coord.lat = static_cast<float>(geometry.value(latTag).toDouble());
    }
    if(geometry.contains(lonTag))
    {
//        auto var = geometry.value(lonTag).toVariant();
//        str11 = var.toString();
        coord.lon = static_cast<float>(geometry.value(lonTag).toDouble());
    }
    return coord;
}
/*
class QVariantHasher {
  public:
    QVariantHasher() : buff(&bb), ds(&buff) {
      bb.reserve(1000);
      buff.open(QIODevice::WriteOnly);
    }
    uint hash(const QVariant & v) {
      buff.seek(0);
      ds << v;
      return qHashBits(bb.constData(), buff.pos());
    }
  private:
    QByteArray bb;
    QBuffer buff;
    QDataStream ds;
};
*/
std::pair<GeoData, CurrentWeatherForecast> getCurrentForecast(QByteArray&& rawBytes)
{
    GeoData geodata;
    QJsonDocument doc = QJsonDocument::fromJson(rawBytes);
    QJsonObject root_object = doc.object();

     CurrentWeatherForecast data;
//     auto arr = root_object.value(weatherAnchor).toArray();
     if(root_object.value(weatherAnchor).isArray())
     {
         QJsonArray arr = root_object.value(weatherAnchor).toArray();
         if(arr.count())
         {
            QJsonObject descr = arr.at(0).toObject();
            fillWeatherTagData(descr, data);
         }
     }

     if(root_object.contains(mainAnchor))
     {
        auto mainObj = root_object.value(mainAnchor).toObject();
        fillMainTagData(mainObj, data);

     }

     fillVisibilityData(root_object, data);
     fillWindSpeedData(root_object, data);

     if(root_object.contains(dtAnchor))
     {
        auto intStrValue = root_object.value(dtAnchor).toInt();
        //auto dtStrValue = root_object.value(dtAnchor).toString();
        data.dt = intStrValue;//dtStrValue.toLongLong();
     }

     if(root_object.contains(nameAnchor))
     {
        data.name = root_object.value(nameAnchor).toString();
        geodata.placeName = data.name;
     }
     coordinates coord;
     if(root_object.contains(coordAnchor))
     {
         QJsonObject geometry = root_object.value(coordAnchor).toObject();
         coord = ParseCoordObject(geometry, placeLat, weatherLon);
         geodata.coord = coord;
     }

     if(root_object.contains(sysAnchor))
     {
         QJsonObject sysObj = root_object.value(sysAnchor).toObject();
         data.sunrise = sysObj.value(sunriseAnchor).toInt();
         data.sunrset = sysObj.value(sunsetAnchor).toInt();
     }

     return {geodata, data};
}

GeoData ParseGeoObject(const QJsonObject& geoObject)
{
    GeoData data;

    if(geoObject.contains(placeConfidense))
        data.confidence = geoObject.value(placeConfidense).toInt();

    if(geoObject.contains(formatted))
        data.placeName = geoObject.value(formatted).toString();

     if(geoObject.contains(placeGeometry))
        {
            QJsonObject geometry = geoObject.value(placeGeometry).toObject();
            data.coord = ParseCoordObject(geometry, placeLat, placeLon);
/*
            if(geometry.contains(placeLat))
                data.coord.lat = geometry.value(placeLat).toDouble();

            if(geometry.contains(placeLng))
                data.coord.lng = geometry.value(placeLng).toDouble();
*/
        }

    return data;
}

geoArray getPlaces(QByteArray&& rawBytes)
{
    QJsonDocument doc = QJsonDocument::fromJson(rawBytes);
    QJsonObject root = doc.object();

    QJsonValue jv = root.value(geoJsonRoot);
    geoArray result;
    if(!jv.isArray())
        return result;

    QJsonArray arr = jv.toArray();
    for(auto i = 0; i < arr.count(); ++i)
        {
             QJsonObject curPlace = arr.at(i).toObject();
             result.push_back(ParseGeoObject(curPlace));
        }

    std::sort(result.begin(), result.end(), [](const auto& obja, const auto& objb){
        return obja.confidence > objb.confidence;
    });
    return result;
}

std::pair<GeoData, forecastArray> getFiveDayForecast(QByteArray&& rawBytes)
{
 //   QByteArray content = std::move(rawBytes);
    QJsonDocument doc = QJsonDocument::fromJson(rawBytes);
    QJsonObject root_object = doc.object();

  //   json::object root_object = value.as_object();
     auto arr = root_object.value(forecastArrayAnchor).toArray();
     GeoData geodata;
     forecastArray res;
     for(auto i = 0; i < arr.size(); ++i)
     {
         auto forecastObj = arr.at(i).toObject();
//         threeHoursWeatherForecast cur;
           CurrentWeatherForecast cur;

         if(forecastObj.value(weatherAnchor).isArray())
              {
                  QJsonArray arr = forecastObj.value(weatherAnchor).toArray();
                  if(arr.count())
                  {
                     QJsonObject descr = arr.at(0).toObject();
                     fillWeatherTagData(descr, cur);
                  }
              }
//         fillWeatherTagData(forecastObj, cur.curForecast);

         auto mainObj = forecastObj.value(mainAnchor).toObject();
         fillMainTagData(mainObj, cur);

         fillVisibilityData(forecastObj, cur);
         fillWindSpeedData(forecastObj, cur);
//         fillForecastWithDate(forecastObj, cur);
         if(forecastObj.contains(dtAnchor))
         {
            auto intStrValue = forecastObj.value(dtAnchor).toInt();
            cur.dt = intStrValue;//dtStrValue.toLongLong();
         }

         res.push_back(cur);
     }

     if(root_object.contains(city))
     {
         auto cityObj = root_object.value(city).toObject();
         QJsonObject geometry = cityObj.value(coordAnchor).toObject();
         geodata.coord = ParseCoordObject(geometry, placeLat, weatherLon);

         if(cityObj.contains(nameAnchor))
           geodata.placeName = cityObj.value(nameAnchor).toString();
     }

     return { geodata, res};
}

ForecastType getForecastType(QByteArray&& rawBytes)
{
    QJsonDocument doc = QJsonDocument::fromJson(rawBytes);
    QJsonObject root_object = doc.object();

    if(root_object.contains(messageAnchor) && root_object.contains(forecastArrayAnchor))
        return ForecastType::FIVE_DAY_FORECAST;

    if(root_object.contains(coordAnchor) && root_object.contains(weatherAnchor) &&
           root_object.contains(mainAnchor))
        return ForecastType::CURRENT_FORECAST;

    return ForecastType::INVALID_FORECAST;
}
//https://openweathermap.org/img/wn/10d.png

//https://raymii.org/s/tutorials/HTTP_GET_requests_in_Qt_and_Qml_async.html
//https://www.youtube.com/watch?v=XWi8WNM4PHQ
//https://www.youtube.com/watch?v=W3ec-_7VPeM
//https://www.youtube.com/watch?v=xXncLUD-4bA
//https://www.youtube.com/watch?v=lTJ-QkC_Sxw
//https://www.youtube.com/watch?v=M7EAW9PKH7A
