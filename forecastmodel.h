#pragma once
#include <map>
#include <optional>
#include "geocoder.h"
#include <set>
class ForecastModel
{
    struct ForecastData
    {
        std::optional<CurrentWeatherForecast> currentForecast{};
        std::optional<forecastArray> fiveDayForecast{};
    };
public:
    ForecastModel();
    void setCurrentForecast(const GeoData& geocoord, const CurrentWeatherForecast& forecast);
    void setFiveDayForecast(const GeoData& geocoord, const forecastArray& forecast);
    std::optional<CurrentWeatherForecast> getCurrentForecast(const GeoData& geocoord);
    std::optional<forecastArray> getFiveDayForecast(const GeoData& geocoord);
    void savePlaces();
    std::vector<GeoData> getPlaces();
    bool locationAlreadyStored(const GeoData& location);
    void deleteStoredLocation(const GeoData& location);
private:
    void restorePlaces();
    std::unordered_map<GeoData, ForecastData,hash_fn> forecastModel;
};
