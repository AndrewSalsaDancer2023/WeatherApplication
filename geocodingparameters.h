#pragma once
#include <QUrlQuery>
#include <geocoder.h>
class QString;

const QString currentForecastPath = "/data/2.5/weather";
const QString fiveDayForecastPath = "/data/2.5/forecast";

QUrlQuery MakeParametersQuery(const QString& geoKey, const QString& location);
QUrl MakeGeocodingUrl(const QString& location);
QUrl MakeWeatherIconUrl(const QString& iconCode);
QUrl MakeWeatherForecastUrl(const QString& path, const float& lat, const float& lng, const QString& units, const QString& lang);
QUrl MakeForecastUrl(ForecastType forecastType, const GeoData& geoData, const QString& units, const QString& lang);
