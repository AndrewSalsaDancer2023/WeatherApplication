#include "settingsdialogcoordinator.h"
#include "settingsdialog.h"
#include "utilities.h"

void SettingsDialogCoordinator::oneDayForecastToggled(bool checked)
{
    if(!checked)
        return;
    tempForecastType = ForecastTypes::currentDay;
}

void SettingsDialogCoordinator::fiveDaysForecastToggled(bool checked)
{
    if(!checked)
        return;
    tempForecastType = ForecastTypes::fiveDays;
}

void SettingsDialogCoordinator::standartUnitsToggled(bool checked)
{
    if(!checked)
        return;
    tempMeasureUnit = MeasureUnits::standard;
}

void SettingsDialogCoordinator::metricUnitsToggled(bool checked)
{
    if(!checked)
        return;
    tempMeasureUnit = MeasureUnits::metric;
}

void SettingsDialogCoordinator::imperialUnitsToggled(bool checked)
{
    if(!checked)
        return;
    tempMeasureUnit = MeasureUnits::imperial;
}

void SettingsDialogCoordinator::langactivated(const QString &lang)
{
    tempLanguage = lang;
}

void SettingsDialogCoordinator::connectSignals(SettingsDialog& dlg)
{
    connect(dlg.getOneDayForecastButton(), SIGNAL(toggled(bool)), this, SLOT(oneDayForecastToggled(bool)));
    connect(dlg.getFiveDaysForecastButton(), SIGNAL(toggled(bool)), this, SLOT(fiveDaysForecastToggled(bool)));

    connect(dlg.getStandartUnitsButton(), SIGNAL(toggled(bool)), this, SLOT(standartUnitsToggled(bool)));
    connect(dlg.getMetricUnitsButton(), SIGNAL(toggled(bool)), this, SLOT(metricUnitsToggled(bool)));
    connect(dlg.getImperialUnitsButton(), SIGNAL(toggled(bool)), this, SLOT(imperialUnitsToggled(bool)));

    connect(dlg.getLanguageCombo(), SIGNAL(activated(const QString &)), this, SLOT(langactivated(const QString &)));
}

void SettingsDialogCoordinator::ShowSettingsDialog(const QList<QString>& langList)
{
    SettingsDialog dlg(langList, curLanguage,
                       curForecastType, curMeasureUnit, mainWindow.get());

    connectSignals(dlg);

    if(dlg.exec() != QDialog::Accepted)
        return;

    if(curForecastType != tempForecastType)
        emit ForecastTypeChanged(tempForecastType);

    if(curMeasureUnit != tempMeasureUnit)
        emit MeasureUnitChanged(tempMeasureUnit);

    if(curLanguage != tempLanguage)
        emit LanguageChanged(tempLanguage);
}
