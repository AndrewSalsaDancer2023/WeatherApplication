#include "geocodingparameters.h"
#include <boost/lexical_cast.hpp>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include "settingstore.h"

/*QString*/ QUrlQuery MakeParametersQuery(const QString& geoKey, const QString& location)
{
    QString locEncoded = QString{QUrl::toPercentEncoding(location).constData()};

    QUrlQuery query;
    query.addQueryItem("q", locEncoded);
    query.addQueryItem("key", geoKey);

    return query;//.toString();
}

QUrl MakeGeocodingUrl(const QString& location)
{
    auto geokey = settingStore::getInstance().getGeocodingKey();
    auto urlQuery = MakeParametersQuery(geokey, location);

    QUrl url;

    url.setScheme("https");
    url.setHost("api.opencagedata.com");
    url.setPath("/geocode/v1/json/");
    url.setQuery(urlQuery);

    Q_ASSERT(url.isValid());
    return url;
}

QUrl MakeWeatherIconUrl(const QString& iconCode)
{
    QUrl url;

    url.setScheme("https");
    url.setHost("openweathermap.org");
    url.setPath("/img/wn/"+iconCode+".png");
//    https://openweathermap.org/img/wn/10d.png
    Q_ASSERT(url.isValid());
    return url;
}



QUrl MakeWeatherForecastUrl(const double& lat, const double& lng, const QString& units, const QString& lang)
{
    auto forecastKey = settingStore::getInstance().getWeatherForecastKey();

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("lat", QString::fromStdString(boost::lexical_cast<std::string>(lat)));
    urlQuery.addQueryItem("lon", QString::fromStdString(boost::lexical_cast<std::string>(lng)));
    urlQuery.addQueryItem("appid", forecastKey);
    urlQuery.addQueryItem("units", units);
    urlQuery.addQueryItem("lang", lang);

    QUrl url;
    url.setScheme("https");
    url.setHost("api.openweathermap.org");
    url.setPath("/data/2.5/weather");
    url.setQuery(urlQuery);

    Q_ASSERT(url.isValid());
    return url;
}
/*
QUrl MakeFiveDaysWeatherForecastUrl(const double& lat, const double& lng, const QString& units, const QString& lang)
{
    auto forecastKey = settingStore::getInstance().getWeatherForecastKey();

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("lat", QString::fromStdString(boost::lexical_cast<std::string>(lat)));
    urlQuery.addQueryItem("lon", QString::fromStdString(boost::lexical_cast<std::string>(lng)));
    urlQuery.addQueryItem("appid", forecastKey);
    urlQuery.addQueryItem("units", units);
    urlQuery.addQueryItem("lang", lang);

    QUrl url;
    url.setScheme("https");
    url.setHost("api.openweathermap.org");
    url.setPath("/data/2.5/forecast");
    url.setQuery(urlQuery);

    Q_ASSERT(url.isValid());
    return url;
}
*/
QUrl MakeWeatherForecastUrl(const QString& path, const float& lat, const float& lng, const QString& units, const QString& lang)
{
    auto forecastKey = settingStore::getInstance().getWeatherForecastKey();

    QUrlQuery urlQuery;
    QString latitude, longitude;
    latitude.setNum(lat, 'g', 6);
    longitude.setNum(lng, 'g', 6);

    urlQuery.addQueryItem("lat", latitude);
    urlQuery.addQueryItem("lon", longitude);
    urlQuery.addQueryItem("appid", forecastKey);
    urlQuery.addQueryItem("units", units);
    urlQuery.addQueryItem("lang", lang);

    QUrl url;
    url.setScheme("https");
    url.setHost("api.openweathermap.org");
    url.setPath(path);
    url.setQuery(urlQuery);

    Q_ASSERT(url.isValid());
    return url;
}

QUrl MakeForecastUrl(ForecastType forecastType, const GeoData& geoData, const QString& units, const QString& lang)
{
    QUrl url;
    if(forecastType == ForecastType::CURRENT_FORECAST)
        url = MakeWeatherForecastUrl(currentForecastPath,geoData.coord.lat, geoData.coord.lon, units, lang);
    else
        if(forecastType == ForecastType::FIVE_DAY_FORECAST)
            url = MakeWeatherForecastUrl(fiveDayForecastPath, geoData.coord.lat, geoData.coord.lon, units, lang);

    qDebug() << url.toString();
    return url;
}
