#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "forecastsettings.h"
#include <map>
#include <QString>

//SettingsDialog::SettingsDialog(const QList<QString>& langList, QWidget *parent) :
SettingsDialog::SettingsDialog(const QList<QString>& langList, const QString& curLanguage,
                                ForecastTypes type, MeasureUnits unit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    std::vector<QRadioButton*> forecastType{ui->oneDayButton, ui->fiveDaysButton};
//    int forecastIndex = static_cast<int>(type);
    forecastType[static_cast<int>(type)]->setChecked(true);

//    ui->oneDayButton->setChecked(true);
//    ui->metricUnitsButton->setChecked(true);

    std::vector<QRadioButton*> unitsType{ui->standartUnitsButton, ui->metricUnitsButton, ui->imperialUnitsButton};
    unitsType[static_cast<int>(unit)]->setChecked(true);


    for(auto it = langList.constBegin(); it != langList.constEnd(); ++it)
        ui->languageComboBox->addItem(*it);

    ui->languageComboBox->setCurrentText(curLanguage);
/*
oneDayButton
fiveDaysButton

standartUnitsButton
metricUnitsButton
imperialUnitsButton

languageComboBox
*/
}

QRadioButton* SettingsDialog::getOneDayForecastButton()
{
    return ui->oneDayButton;
}

QRadioButton* SettingsDialog::getFiveDaysForecastButton()
{
    return ui->fiveDaysButton;
}

QRadioButton* SettingsDialog::getStandartUnitsButton()
{
    return ui->standartUnitsButton;
}

QRadioButton* SettingsDialog::getMetricUnitsButton()
{
    return ui->metricUnitsButton;
}

QRadioButton* SettingsDialog::getImperialUnitsButton()
{
    return ui->imperialUnitsButton;
}

QComboBox* SettingsDialog::getLanguageCombo()
{
    return ui->languageComboBox;
}

SettingsDialog::~SettingsDialog()
{
//    int ind = ui->languageComboBox->currentIndex();
//    QString text = ui->languageComboBox->currentText();

    delete ui;
}
