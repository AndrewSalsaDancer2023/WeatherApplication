#pragma once
#include <QString>
#include <QList>
#include "utilities.h"

class ForecastSettings
{
public:
    ForecastSettings(ForecastTypes type = ForecastTypes::currentDay,
                     MeasureUnits unit = MeasureUnits::metric, const QString& language = "English");

    void setForecastType(ForecastTypes type) { forecastType = type;}
    void setmeasureUnit(MeasureUnits unit) { measureUnit = unit;}
    void setLanguage(const QString& language) { curLanguage = language;}

    ForecastTypes getForecastType() { return forecastType;}
//   QString getForecastTypeAsString();
    MeasureUnits getMeasureUnit() {return measureUnit;}
    QString getMeasureUnitAsString();
    QString getForecastLanguage() {return curLanguage;}

    QString getLanguageCode();
    QList<QString> getLanguageList();

    void saveSettings();
    void restoreSettings();
private:
    ForecastTypes forecastType;
    MeasureUnits measureUnit;
    QString curLanguage;
};


