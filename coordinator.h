#pragma once
#include <functional>
#include <map>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include "weatherwindow.h"
#include <memory>
#include <optional>
#include "contentdownloader.h"
#include "geocoder.h"
#include "forecastmodel.h"
#include "imagecache.h"
#include "threadsupport.h"
#include <QApplication>
#include <functional>

class ShortForecastWidget;
class DetailForecastWidget;
class fiveDayForecastWidget;
class ForecastSettings;
class SettingsDialogCoordinator;

enum class ForecastTypes;
enum class MeasureUnits;

Q_DECLARE_METATYPE(result_type);

class Coordinator : public QObject
{
   Q_OBJECT

public:
    Coordinator(QApplication& app);
    ~Coordinator();
    void ShowMainWindow();
    void FillShortForecastList();
signals:
    void FillLocationList(const std::vector<QString>& locNames);
    void currentForecastObtained(const CurrentWeatherForecast& data);
    void AddShortForecastWidgetToList(ShortForecastWidget* widget);
    void FillDetailedForecastList(DetailForecastWidget* widget);
    void FillFiveDayForecastList(fiveDayForecastWidget* widget);

    void forecastObtained(result_type);
    void forecastSaved(result_type);
    void weatherImageObtained(QString, unsigned);
    void clearDetailForecastList();
public slots:
    void ShowAddLocationDialog();
    void ShowSettingsDialog();
    void startSearchLocation(const QString& locName);
    void deleteAssociatedData(unsigned widgetId);
    void selectedLocationChanged(unsigned widgetId);
    void quitApp();
//private slots:
    std::optional<GeoData> getSelectedLocation(const QString& locName);
private slots:
//    void handleResults(result_type );
    void handleWeatherForecastResponce(result_type );
    void refreshGUI(result_type coord);
    void setForecastImage(QString imgName, unsigned widgetId);

    void ForecastTypeChanged(ForecastTypes);
    void MeasureUnitChanged(MeasureUnits);
    void LanguageChanged(QString);

private:
    result_type handleForecast(const QByteArray& jsonResp);
    unsigned getWidgetId();
    void GetForecast(ForecastType forecastType, const GeoData& geoData, const QString& units, const QString& lang, std::function<void(result_type)> guiRefresh);

    void saveDailyForecast(const GeoData& geodata, const CurrentWeatherForecast& data);
    void saveFiveDaysForecast(const GeoData& geodata, const forecastArray& forecast);
    ShortForecastWidget* fillShortForecastWidget(const CurrentWeatherForecast& data);
    void fillDetailForecastWidget(const forecastArray& array);
    void fillFiveDayForecastWidget(const forecastArray& array);

    std::unique_ptr<WeatherWindow> mainWindow;
    std::unique_ptr<ContentDownloader> downloader;
    std::unique_ptr<ForecastModel> forecastModel;
    std::unique_ptr<ImageCache> imageCache;
    std::unique_ptr<ForecastSettings> appSettings;
    QueueThread* pQueueThread{};
    std::shared_ptr<WorkQueue> command_queue;
    std::unique_ptr<SettingsDialogCoordinator> settingsDialogCoordinator;
    geoArray locationVariants;

    unsigned widgetId{};
    std::unordered_map<GeoData, unsigned,hash_fn> dataWidgetIdBindMap;
    QApplication& application;
};

