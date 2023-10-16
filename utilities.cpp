#include "utilities.h"
#include <QDateTime>
#include <QTimeZone>
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include <functional>
#include "shortforecastwidget.h"
#include "detailforecastwidget.h"
#include "fivedayforecastwidget.h"

std::vector<QString> convertToStringList(const geoArray& places)
{
    std::vector<QString> result;
    for(const auto& geoObject: places)
        result.push_back(geoObject.placeName);

    return result;
}

QString convertDateTimeToString(unsigned long long dt)
{
    auto res = QDateTime::fromSecsSinceEpoch(dt, QTimeZone::systemTimeZone());// dt(QDate::currentDate());
    return res.date().toString() + " " + res.time().toString();
}

QString convertTimeToString(unsigned long long dt)
{
    auto res = QDateTime::fromSecsSinceEpoch(dt, QTimeZone::systemTimeZone());
    return res.time().toString();
}

QString deleteSeconds(const QString& strTime)
{
    int last = strTime.lastIndexOf(':');
    if(last < 0)
        return strTime;

    return strTime.left(last);
}

ShortForecastWidget* createForecastWidget(unsigned id, const QString& placeName)
{
    auto widget = new ShortForecastWidget(id);//(this);
    widget->setLocationName(placeName);

    return widget;
}

ShortForecastWidget* createForecastWidget(unsigned id, const CurrentWeatherForecast& data, QPixmap* pixmap)
{
    auto widget = new ShortForecastWidget(id);//(this);
    widget->setLocationName(data.name);
    widget->setTemperature(QString::number(data.temperCurrent));
    if(pixmap)
        widget->setForecastIcon(*pixmap);

    return widget;
}

DetailForecastWidget* createDetailForecastWidget(const CurrentWeatherForecast& data)
{
    auto widget = new DetailForecastWidget();//this);

    widget->setDate(deleteSeconds(convertDateTimeToString(data.dt)));
    widget->setLocation(data.name);
    widget->setDescription(data.description);

    widget->setCurrentTemperature(QString::number(data.temperCurrent));
    widget->setMinTemperature(QString::number(data.temperMin));
    widget->setMaxTemperature(QString::number(data.temperMax));

    widget->setWindSpeed(QString::number(static_cast<int>(data.windSpeed)));
    widget->setPreasure(QString::number(data.pressure));
    widget->setHumidity(QString::number(data.humidity));

    widget->setVisibility(QString::number(data.visibility));
    widget->setSunriseTime(deleteSeconds(convertTimeToString(data.sunrise)));
    widget->setSunsetTime(deleteSeconds(convertTimeToString(data.sunrset)));

    return widget;
}

fiveDayForecastWidget* createFiveDayForecastWidget(const CurrentWeatherForecast& data)
{
    auto widget = new fiveDayForecastWidget();//this);

    widget->setDate(deleteSeconds(convertDateTimeToString(data.dt)));
//    widget->setLocation(data.name);
    widget->setDescription(data.description);

    widget->setCurrentTemperature(QString::number(data.temperCurrent));
    widget->setMinTemperature(QString::number(data.temperMin));
    widget->setMaxTemperature(QString::number(data.temperMax));

    widget->setWindSpeed(QString::number(static_cast<int>(data.windSpeed)));
    widget->setPreasure(QString::number(data.pressure));
    widget->setHumidity(QString::number(data.humidity));

    widget->setVisibility(QString::number(data.visibility));
//    widget->setSunriseTime(deleteSeconds(convertTimeToString(data.sunrise)));
//    widget->setSunsetTime(deleteSeconds(convertTimeToString(data.sunrset)));

    return widget;
}

//void storeGraphicFile(const QUrl& url, const QByteArray& ba)
void storeGraphicFile(const QUrl& url)
{
    //QString res1 = url.path().section('/', -1);
    QString strFileName = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+
            "/"+url.path().section('/', -1);

    qDebug() << strFileName;
    if(QFile::exists(strFileName))
        qDebug() << "File Exists";
    else
        qDebug() << "File absent";
  /*  QFile file(strFileName);
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(ba);
    file.close();*/
}

void showPicture(const QString& fileName)
{
    QPixmap pix(fileName);
/*    QLabel* plbl = new QLabel;
    plbl->setPixmap(pix)
    plbl->setFixedSize(pix.size());
    plbl->show();*/
}

QString convertMeasureUnitsToString(MeasureUnits unit)
{
    switch(unit)
    {
       case MeasureUnits::standard:
        return "°K";
        break;
       case MeasureUnits::metric:
        return "°C";
        break;
       default:
        return "°F";
    }
}

//https://www.youtube.com/watch?v=D-lTwGJRx0o
//https://www.qt.io/blog/asynchronous-apis-in-qt-6
//https://www.youtube.com/watch?v=tvpC8UrPpZ4
//https://www.youtube.com/watch?v=PR6wVy7Et1A
//https://www.youtube.com/watch?v=W3ec-_7VPeM
//https://www.youtube.com/watch?v=lTJ-QkC_Sxw
//https://www.youtube.com/watch?v=ocsBQNyrCMM
//https://www.youtube.com/watch?v=eD6E4wpA4Eg














