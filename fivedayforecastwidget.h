#ifndef FIVEDAYFORECASTWIDGET_H
#define FIVEDAYFORECASTWIDGET_H

#include <QWidget>

namespace Ui {
class fiveDayForecastWidget;
}

class fiveDayForecastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fiveDayForecastWidget(QWidget *parent = nullptr);
    ~fiveDayForecastWidget();

    void setDate(const QString& date);
    void setDescription(const QString& description);

    void setCurrentTemperature(const QString& currTemerature);
    void setMinTemperature(const QString& minTemerature);
    void setMaxTemperature(const QString& maxTemerature);

    void setWindSpeed(const QString& windSpeed);
    void setPreasure(const QString& preasure);
    void setHumidity(const QString& humidity);

    void setVisibility(const QString& windSpeed);

private:
    Ui::fiveDayForecastWidget *ui;
};

#endif // FIVEDAYFORECASTWIDGET_H
