#pragma once
#include <QByteArray>
#include <QString>
#include <QVector>
#include <utility>
#include <math.h>
#include <unordered_map>

const float epsilon = 0.001f;

enum class ForecastType : int
{
    CURRENT_FORECAST,
    FIVE_DAY_FORECAST,
    INVALID_FORECAST
};

class coordinates
{
public:
    coordinates() = default;
    ~coordinates() = default;
    coordinates(const coordinates &) = default;
    coordinates &operator=(const coordinates &) = default;

    float lat{};
    float lon{};

    bool operator == (const coordinates& rhs) const
    {
        return  ((std::fabs(rhs.lat - this->lat) <= epsilon) && (std::fabs(rhs.lon - this->lon) <= epsilon));
    }

};


class GeoData
{
public:
    GeoData() = default;
    ~GeoData() = default;
    GeoData(const GeoData &) = default;
    GeoData &operator=(const GeoData &) = default;

    // `operator==` is required to compare keys in case of a hash collision
    bool operator== (const GeoData &other) const
    {
        return (coord == other.coord);
    }

    coordinates coord;
    int confidence{};
    QString placeName;
};

// The specialized hash function for `unordered_map` keys
struct hash_fn
{
    std::size_t operator() (const GeoData &data) const
    {
        std::size_t h1 = std::hash<size_t>()(data.coord.lat*1000);
        std::size_t h2 = std::hash<size_t>()(data.coord.lon*1000);

        return h1 ^ h2;
    }
};

//std::unordered_map<Node<std::string, std::string>, int, hash_fn> u_map;

typedef std::vector<GeoData> geoArray;

class CurrentWeatherForecast
{
public:
    CurrentWeatherForecast() = default;
    ~CurrentWeatherForecast() = default;
    CurrentWeatherForecast(const CurrentWeatherForecast &) = default;
    CurrentWeatherForecast &operator=(const CurrentWeatherForecast &) = default;
    int temperCurrent;
    int temperMin;
    int temperMax;
    double windSpeed;
    int pressure;
    int humidity;
    int visibility;
    unsigned long long dt;
    unsigned long long sunrise;
    unsigned long long sunrset;
    QString name;
    QString description;
    QString icon;
};

struct threeHoursWeatherForecast
{
    CurrentWeatherForecast curForecast;
    QString forecastTimeString;
};

//typedef std::vector<threeHoursWeatherForecast> fiveDayForecast;
typedef QVector<CurrentWeatherForecast> forecastArray;


   std::vector<QString> convertToStringList(const geoArray& places);
   geoArray getPlaces(QByteArray&& rawBytes);
   std::pair<GeoData, CurrentWeatherForecast> getCurrentForecast(QByteArray&& rawBytes);
   std::pair<GeoData, forecastArray> getFiveDayForecast(QByteArray&& rawBytes);
   ForecastType getForecastType(QByteArray&& rawBytes);

/*
72, 148 145

«Параллельное	выполнение	различных	задач

Обратитесь	 к  главе	 5	 «Многопоточность»	для	 получения	дополнительной	информации	о Boost.Thread	и атомарных	операциях;
 для	 получения	 дополнительной	 информации	 о  Boost.Bind см.	 рецепт
«Привязка и переупорядочение параметров функции»	главы	1	«Приступаем
к написанию	приложения»;
 обратитесь	к рецепту	«Приведение умных указателей»	главы	3	для	получения		информации	о том,	как	преобразовать	shared_ptr<U>	в shared_ptr<T>;
 документация	по	библиотеке	Boost.SmartPtr	содержит	множество	примеров и другую	полезную	информацию	обо	всех	классах	умного	указателя.
Перейдите	по	ссылке	http://boost.org/libs/smart_ptr,	чтобы	прочитать	о них.

рецепт	«Передача указателя на функцию в переменной»;

 рецепт	«Передача лямбда-функций C++11 в переменной»


QThread::currentThread();
uWebSockets

*/


