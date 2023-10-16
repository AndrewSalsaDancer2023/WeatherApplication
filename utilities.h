#pragma once
#include "geocoder.h"
#include <vector>
#include <QString>
#include <QUrl>
#include <QPixmap>

class ShortForecastWidget;
class DetailForecastWidget;
class fiveDayForecastWidget;

enum class MeasureUnits
{
  standard = 0,
  metric,
  imperial
};

enum class ForecastTypes
{
  currentDay = 0,
  fiveDays
};

std::vector<QString> convertToStringList(const geoArray& places);
QString convertMeasureUnitsToString(MeasureUnits unit);
QString convertDateTimeToString(unsigned long long dt);
QString convertTimeToString(unsigned long long dt);
QString deleteSeconds(const QString& strTime);
//void storeGraphicFile(const QUrl& url, const QByteArray& ba)
void storeGraphicFile(const QUrl& url);
ShortForecastWidget* createForecastWidget(unsigned id, const CurrentWeatherForecast& data, QPixmap* pixmap = nullptr);
ShortForecastWidget* createForecastWidget(unsigned id, const QString& placeName);
DetailForecastWidget* createDetailForecastWidget(const CurrentWeatherForecast& data);
fiveDayForecastWidget* createFiveDayForecastWidget(const CurrentWeatherForecast& data);
void showPicture(const QString& fileName);





















