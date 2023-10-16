#ifndef SHORTFORECASTWIDGET_H
#define SHORTFORECASTWIDGET_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ShortForecastWidget;
}

class ShortForecastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShortForecastWidget(unsigned widgetId, QWidget *parent = nullptr);
    ~ShortForecastWidget();

    void setLocationName(const QString& locationTitle);
    QString getLocationName();
    void setTemperature(const QString& temperature);
    void setForecastIcon(const QPixmap &img);
    void setMeasureUnit(const QString& unit);
    unsigned getWidgetId() { return id;}
private:
    Ui::ShortForecastWidget *ui;
    unsigned id{};
};

#endif // SHORTFORECASTWIDGET_H
