#ifndef DETAILFORECASTWIDGET_H
#define DETAILFORECASTWIDGET_H

#include <QWidget>

namespace Ui {
class DetailForecastWidget;
}

class DetailForecastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetailForecastWidget(QWidget *parent = nullptr);
    ~DetailForecastWidget();

    void setDate(const QString& date);
    void setLocation(const QString& location);
    void setDescription(const QString& description);

    void setCurrentTemperature(const QString& currTemerature);
    void setMinTemperature(const QString& minTemerature);
    void setMaxTemperature(const QString& maxTemerature);

    void setWindSpeed(const QString& windSpeed);
    void setPreasure(const QString& preasure);
    void setHumidity(const QString& humidity);

    void setVisibility(const QString& windSpeed);
    void setSunriseTime(const QString& riseTime);
    void setSunsetTime(const QString& sunsetTime);
private:
    Ui::DetailForecastWidget *ui;
};

#endif // DETAILFORECASTWIDGET_H
