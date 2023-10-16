#pragma once
#include <memory>
//#include "forecastsettings.h"
#include <QList>
#include "weatherwindow.h"

#include <QObject>
enum class ForecastTypes;
enum class MeasureUnits;
class SettingsDialog;

class SettingsDialogCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit SettingsDialogCoordinator(ForecastTypes forecastType, MeasureUnits measureUnit,
                                       const QString& language, std::unique_ptr<WeatherWindow>& parentWindow)
        : curForecastType{forecastType}, curMeasureUnit{measureUnit}, curLanguage{language}, mainWindow{parentWindow}
    {
        tempForecastType = curForecastType;
        tempMeasureUnit = curMeasureUnit;
        tempLanguage = curLanguage;

    }
    void ShowSettingsDialog(const QList<QString>& langList);

signals:
    void ForecastTypeChanged(ForecastTypes);
    void MeasureUnitChanged(MeasureUnits);
    void LanguageChanged(QString);

public slots:
    void oneDayForecastToggled(bool checked);
    void fiveDaysForecastToggled(bool checked);
    void standartUnitsToggled(bool checked);
    void metricUnitsToggled(bool checked);
    void imperialUnitsToggled(bool checked);
    void langactivated(const QString &lang);

private:
    void connectSignals(SettingsDialog& dlg);

    ForecastTypes curForecastType;
    MeasureUnits curMeasureUnit;
    QString curLanguage;


    ForecastTypes tempForecastType;
    MeasureUnits tempMeasureUnit;
    QString tempLanguage;

    std::unique_ptr<WeatherWindow>& mainWindow;
};
