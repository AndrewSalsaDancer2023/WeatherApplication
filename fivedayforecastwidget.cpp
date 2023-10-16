#include "fivedayforecastwidget.h"
#include "ui_fivedayforecastwidget.h"

fiveDayForecastWidget::fiveDayForecastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fiveDayForecastWidget)
{
    ui->setupUi(this);
}

fiveDayForecastWidget::~fiveDayForecastWidget()
{
    delete ui;
}

void fiveDayForecastWidget::setDate(const QString& date)
{
    ui->date->setText(date);
}

void fiveDayForecastWidget::setDescription(const QString& description)
{
    ui->description->setText(description);
}

void fiveDayForecastWidget::setCurrentTemperature(const QString& currTemerature)
{
    ui->temp_current->setText(currTemerature);
}

void fiveDayForecastWidget::setMinTemperature(const QString& minTemerature)
{
    ui->temp_min->setText(minTemerature);
}

void fiveDayForecastWidget::setMaxTemperature(const QString& maxTemerature)
{
    ui->temp_max->setText(maxTemerature);
}

void fiveDayForecastWidget::setWindSpeed(const QString& windSpeed)
{
    ui->wind->setText(windSpeed);
}

void fiveDayForecastWidget::setPreasure(const QString& preasure)
{
    ui->preasure->setText(preasure);
}

void fiveDayForecastWidget::setHumidity(const QString& humidity)
{
    ui->humidity->setText(humidity);
}

void fiveDayForecastWidget::setVisibility(const QString& windSpeed)
{
    ui->visibility->setText(windSpeed);
}
