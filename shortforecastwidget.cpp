#include "shortforecastwidget.h"
#include "ui_shortforecastwidget.h"

ShortForecastWidget::ShortForecastWidget(unsigned widgetId, QWidget *parent) :
    QWidget(parent),
    id{widgetId},
    ui(new Ui::ShortForecastWidget)
{
    ui->setupUi(this);
}

ShortForecastWidget::~ShortForecastWidget()
{
    delete ui;
}

void ShortForecastWidget::setLocationName(const QString& locationTitle)
{
    ui->location->setText(locationTitle);
}

QString ShortForecastWidget::getLocationName()
{
    return ui->location->text();
}

void ShortForecastWidget::setTemperature(const QString& temperature)
{
    ui->temperature->setText(temperature);
}

void ShortForecastWidget::setForecastIcon(const QPixmap &img)
{
    ui->weatherIcon->setPixmap(img);
}

void ShortForecastWidget::setMeasureUnit(const QString& unit)
{
    ui->unit->setText(unit);
}

//https://stackoverflow.com/questions/5653114/display-image-in-qt-to-fit-label-size
//https://www.youtube.com/watch?v=SMWSF7MdJmI
