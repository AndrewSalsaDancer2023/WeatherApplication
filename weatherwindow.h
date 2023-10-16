#ifndef WEATHERWINDOW_H
#define WEATHERWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QListWidget>
#include "addlocationdialog.h"
#include <optional>
#include "settingstore.h"
#include "geocoder.h"
#include <memory>

class ContentDownloader;
class Coordinator;
class ShortForecastWidget;
class DetailForecastWidget;
class fiveDayForecastWidget;
//#include <QListWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class WeatherWindow; }
QT_END_NAMESPACE

class WeatherWindow : public QMainWindow
{
    Q_OBJECT

public:
    WeatherWindow(QWidget *parent = nullptr);
    ~WeatherWindow();
    void deleteWidgetFromList(QListWidget* pList, int row);
    bool WidgetInShortForecastList(ShortForecastWidget* widget);
    ShortForecastWidget* getShortForecastWidget(unsigned widgetId);
    unsigned getNumItemsInDetailedForecastList();

signals:
    void showAddLocationDialog();
    void showSettingsDialog();
    void locationSelected(unsigned);
    void quitApp();
    void deleteAssociatedData(unsigned widgetId);
public slots:
    void AddShortForecastWidgetToList(ShortForecastWidget* widget);
    void FillDetailedForecastList(DetailForecastWidget* widget);
    void FillFiveDayForecastList(fiveDayForecastWidget* widget);
    void deleteWidgetsFromDetailForecastList();
    void shortForecastWidgetSelectionChanged();
//private:
void AddLocationClicked();
private:
void RemoveLocationClicked()
{
    qDebug() << "remove clicked";
}

private slots:
void on_actionAdd_location_triggered();
void on_actionDelete_location_triggered();
void on_actionQuit_triggered();

void on_actionSettings_triggered();

void on_shortForecastWidget_itemClicked(QListWidgetItem *item);

private:
    void FillForecastList();
private:
    Ui::WeatherWindow *ui;
  //  std::unique_ptr<ContentDownloader> downloader;
  //  Coordinator& coordinator;
};
#endif // WEATHERWINDOW_H
