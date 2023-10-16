#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QRadioButton>
#include <QComboBox>
#include <QDialog>

enum class ForecastTypes;
enum class MeasureUnits;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(const QList<QString>& langList, const QString& curLanguage,
                            ForecastTypes type, MeasureUnits unit, QWidget *parent = nullptr);
    ~SettingsDialog();
    QRadioButton* getOneDayForecastButton();
    QRadioButton* getFiveDaysForecastButton();
    QRadioButton* getStandartUnitsButton();
    QRadioButton* getMetricUnitsButton();
    QRadioButton* getImperialUnitsButton();
    QComboBox* getLanguageCombo();


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
