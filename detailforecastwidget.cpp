#include "detailforecastwidget.h"
#include "ui_detailforecastwidget.h"

DetailForecastWidget::DetailForecastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailForecastWidget)
{
    ui->setupUi(this);
}

DetailForecastWidget::~DetailForecastWidget()
{
    delete ui;
}


void DetailForecastWidget::setDate(const QString& date)
{
    ui->date->setText(date);
}
void DetailForecastWidget::setLocation(const QString& location)
{
    ui->location->setText(location);
}

void DetailForecastWidget::setDescription(const QString& description)
{
    ui->description->setText(description);
}

void DetailForecastWidget::setCurrentTemperature(const QString& currTemerature)
{
    ui->temp_current->setText(currTemerature);
}

void DetailForecastWidget::setMinTemperature(const QString& minTemerature)
{
    ui->temp_min->setText(minTemerature);
}

void DetailForecastWidget::setMaxTemperature(const QString& maxTemerature)
{
    ui->temp_max->setText(maxTemerature);
}

void DetailForecastWidget::setWindSpeed(const QString& windSpeed)
{
    ui->wind->setText(windSpeed);
}

void DetailForecastWidget::setPreasure(const QString& preasure)
{
    ui->preasure->setText(preasure);
}

void DetailForecastWidget::setHumidity(const QString& humidity)
{
    ui->humidity->setText(humidity);
}

void DetailForecastWidget::setVisibility(const QString& windSpeed)
{
    ui->visibility->setText(windSpeed);
}

void DetailForecastWidget::setSunriseTime(const QString& riseTime)
{
    ui->sunrise->setText(riseTime);
}

void DetailForecastWidget::setSunsetTime(const QString& sunsetTime)
{
    ui->sunset->setText(sunsetTime);
}
