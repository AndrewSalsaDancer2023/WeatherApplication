#include "coordinator.h"
#include "addlocationdialog.h"
#include "settingsdialog.h"
#include <QMessageBox>
#include "geocodingparameters.h"
#include "settingstore.h"
#include "contentdownloader.h"
#include "shortforecastwidget.h"
#include "fivedayforecastwidget.h"
#include "settingsdialogcoordinator.h"
#include "utilities.h"
#include "geocoder.h"
#include <forecastsettings.h>
#include <algorithm>
#include <optional>
#include <QUrl>
#include <QStandardPaths>
#include <QRadioButton>

Coordinator::Coordinator(QApplication& app)
    :mainWindow{std::make_unique<WeatherWindow>()}, application{app}
{
    connect(mainWindow.get(), SIGNAL(showAddLocationDialog()), this, SLOT(ShowAddLocationDialog()));
    connect(mainWindow.get(), SIGNAL(showSettingsDialog()), this, SLOT(ShowSettingsDialog()));
    downloader = std::make_unique<ContentDownloader>();

    connect(this, SIGNAL(AddShortForecastWidgetToList(ShortForecastWidget*)),
            mainWindow.get(), SLOT(AddShortForecastWidgetToList(ShortForecastWidget*))) ;

    connect(this, SIGNAL(FillDetailedForecastList(DetailForecastWidget*)),
            mainWindow.get(), SLOT(FillDetailedForecastList(DetailForecastWidget*))) ;

    connect(this, SIGNAL(FillFiveDayForecastList(fiveDayForecastWidget*)),
            mainWindow.get(), SLOT(FillFiveDayForecastList(fiveDayForecastWidget*))) ;

    connect(mainWindow.get(), SIGNAL(locationSelected(unsigned)), this, SLOT(selectedLocationChanged(unsigned))) ;
    connect(this, SIGNAL(clearDetailForecastList()), mainWindow.get(), SLOT(deleteWidgetsFromDetailForecastList())) ;

    connect(mainWindow.get(), SIGNAL(quitApp()), this, SLOT(quitApp()));
    connect(mainWindow.get(), SIGNAL(deleteAssociatedData(unsigned)), this, SLOT(deleteAssociatedData(unsigned)));

    forecastModel = std::make_unique<ForecastModel>();
    imageCache = std::make_unique<ImageCache>(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));

    appSettings = std::make_unique<ForecastSettings>();
    appSettings->restoreSettings();

    settingsDialogCoordinator = std::make_unique<SettingsDialogCoordinator>(appSettings->getForecastType(), appSettings->getMeasureUnit(), appSettings->getForecastLanguage(), mainWindow);

    connect(settingsDialogCoordinator.get(), SIGNAL(ForecastTypeChanged(ForecastTypes)), this, SLOT(ForecastTypeChanged(ForecastTypes)));
    connect(settingsDialogCoordinator.get(), SIGNAL(MeasureUnitChanged(MeasureUnits)), this, SLOT(MeasureUnitChanged(MeasureUnits)));
    connect(settingsDialogCoordinator.get(), SIGNAL(LanguageChanged(QString)), this, SLOT(LanguageChanged(QString)));

    qRegisterMetaType<result_type>();
    command_queue = std::make_unique<WorkQueue>();
    pQueueThread = new QueueThread();

    connect(this, SIGNAL(forecastObtained(result_type)), this, SLOT(handleWeatherForecastResponce(result_type)));
    connect(this, SIGNAL(forecastSaved(result_type)), this, SLOT(refreshGUI(result_type)));
    connect(this, SIGNAL(weatherImageObtained(QString, unsigned)), this, SLOT(setForecastImage(QString, unsigned)));

    connect(pQueueThread, SIGNAL(finished()), pQueueThread, SLOT(deleteLater()));
    pQueueThread->setWorkQueue(command_queue.get());
    pQueueThread->start();
}

void Coordinator::ShowMainWindow()
{
    mainWindow->show();
}

void Coordinator::quitApp()
{
    application.quit();
}

void Coordinator::FillShortForecastList()
{
/*    auto places = forecastModel->getPlaces();
    for(const auto& place : places)
    {
        ShortForecastWidget* pwidget = createForecastWidget(getWidgetId(), place.placeName);
        pwidget->setMeasureUnit(convertMeasureUnitsToString(appSettings->getMeasureUnit()));
        emit AddShortForecastWidgetToList(pwidget);
        dataWidgetIdBindMap[place] = pwidget->getWidgetId();
        GetForecast(ForecastType::CURRENT_FORECAST, place,
                       appSettings->getMeasureUnitAsString(), appSettings->getLanguageCode(),
                       [this](result_type res ){
                        emit forecastSaved(res);
        });
    }
*/
}

Coordinator::~Coordinator()
{
    imageCache->storeFilesInfo();
    forecastModel->savePlaces();
    appSettings->saveSettings();
    command_queue->push_task(task_type());
    pQueueThread->quit();
    pQueueThread->wait();
}

void ShowErrorMessage(const QString& message)
{
    QMessageBox msgBox;//this);
    msgBox.setText(message);//"Location already stored. Please try another one!");
    msgBox.exec();
}

result_type Coordinator::handleForecast(const QByteArray& jsonResp)
{
    ForecastType respType = getForecastType(QByteArray(jsonResp));
    if(respType == ForecastType::FIVE_DAY_FORECAST)
    {
         const auto& [geoData, forecast] = getFiveDayForecast(QByteArray(jsonResp));
         saveFiveDaysForecast(geoData, forecast);
         return {respType, geoData };
     }
     else
         if(respType == ForecastType::CURRENT_FORECAST)
         {
             const auto& [geoData, forecast] = getCurrentForecast(QByteArray(jsonResp));
             saveDailyForecast(geoData, forecast);
             return {respType, geoData };
         }
    return {respType, GeoData() };
}

void Coordinator::GetForecast(ForecastType forecastType, const GeoData& geoData, const QString& units, const QString& lang, std::function<void(result_type)> guiRefresh)
{
    auto url = MakeForecastUrl(forecastType, geoData, units, lang);
    auto responce = [this, guiRefresh](QByteArray&& jsonResp)
    {
        command_queue->push_task([this, jsonResp, guiRefresh](){
            auto res = handleForecast(jsonResp);
            if(guiRefresh)
                guiRefresh(res);
//            emit forecastObtained(res);
               });
    };

    downloader->StartDownload(url.toString(), responce);
}

void Coordinator::ShowAddLocationDialog()
{
    AddLocationDialog dlg(mainWindow.get());

    connect(&dlg, SIGNAL(startSearchLocation(const QString&)),
    this, SLOT(startSearchLocation(const QString&)));

    connect(this, SIGNAL(FillLocationList(const std::vector<QString>&)),
            &dlg, SLOT(FillLocationList(const std::vector<QString>&)));

    if(dlg.exec() != QDialog::Accepted)
        return;

    auto placeTitle = dlg.getSelectedPlaceTitle();
    if(!placeTitle)
            return;

    std::optional<GeoData> geoData = getSelectedLocation(*placeTitle);
   if(geoData && forecastModel->locationAlreadyStored(*geoData))
    {
        qDebug() << "Add location:" << *placeTitle;
        ShowErrorMessage("Location already stored. Please try another one!");
        return;
    }

   GetForecast(ForecastType::CURRENT_FORECAST, *geoData,
               appSettings->getMeasureUnitAsString(),
               appSettings->getLanguageCode(), [this](result_type res){
                emit forecastObtained(res);
       });

//    GetForecast(ForecastType::CURRENT_FORECAST, *geoData, appSettings->getMeasureUnitAsString(), appSettings->getLanguageCode());
//    GetForecast(ForecastType::FIVE_DAY_FORECAST, *geoData);
}

void Coordinator::ForecastTypeChanged(ForecastTypes type)
{
    appSettings->setForecastType(type);
}

void Coordinator::MeasureUnitChanged(MeasureUnits unit)
{
    appSettings->setmeasureUnit(unit);
}

void Coordinator::LanguageChanged(QString lang)
{
    appSettings->setLanguage(lang);
}

void Coordinator::ShowSettingsDialog()
{
    settingsDialogCoordinator->ShowSettingsDialog(appSettings->getLanguageList());
}

void Coordinator::handleWeatherForecastResponce(result_type coord)
{
    if(coord.first == ForecastType::FIVE_DAY_FORECAST)
    {
        std::optional<forecastArray> forecast = forecastModel->getFiveDayForecast(coord.second);
        if(!forecast)
            return;

        fillFiveDayForecastWidget(*forecast);
    }
    else
    if(coord.first == ForecastType::CURRENT_FORECAST)
    {
        std::optional<CurrentWeatherForecast> forecast = forecastModel->getCurrentForecast(coord.second);
        if(!forecast)
            return;
        auto shortw = fillShortForecastWidget(*forecast);
        dataWidgetIdBindMap[coord.second] = shortw->getWidgetId();
        if(!mainWindow->getNumItemsInDetailedForecastList())
            fillDetailForecastWidget({*forecast});
    }
}

void Coordinator::setForecastImage(QString imgName, unsigned widgetId)
{
    ShortForecastWidget* pWidget = mainWindow->getShortForecastWidget(widgetId);
    if(!pWidget)
        return;

     if(auto img = imageCache->getImage(imgName))
        pWidget->setForecastIcon(*img);
}

void Coordinator::refreshGUI(result_type coord)
{
     auto itFind = dataWidgetIdBindMap.find(coord.second);
     if(itFind != dataWidgetIdBindMap.end())
     {
        std::optional<CurrentWeatherForecast> forecast = forecastModel->getCurrentForecast(coord.second);
        if(!forecast)
            return;
       auto widgetId = itFind->second;
       ShortForecastWidget* pWidget = mainWindow->getShortForecastWidget(itFind->second);
       if(pWidget)
           pWidget->setTemperature(QString::number((*forecast).temperCurrent));

       auto imgTitle = (*forecast).icon+".png";
       auto url = MakeWeatherIconUrl((*forecast).icon);
       auto responce = [this, imgTitle, widgetId](QByteArray&& jsonResp)
       {
           command_queue->push_task([this, imgTitle, widgetId, jsonResp](){
                          imageCache->storeImage(imgTitle, std::move(jsonResp));
                           emit weatherImageObtained(imgTitle, widgetId);
                  });
       };

       auto img = imageCache->getImage(imgTitle);
       if(!img)
         downloader->StartDownload(url.toString(), responce);
       else
           pWidget->setForecastIcon(*img);

       auto places = forecastModel->getPlaces();
       if(places.empty())
           return;

       if((places[0] == coord.second) && !mainWindow->getNumItemsInDetailedForecastList())
            fillDetailForecastWidget({*forecast});
    }
}

std::optional<GeoData> Coordinator::getSelectedLocation(const QString& locName)
{
    auto it = std::find_if(locationVariants.begin(), locationVariants.end(), [&locName](GeoData& elem){
        return elem.placeName == locName;
    });

    if(it != locationVariants.end())
        return {*it};


    return std::nullopt;
}

void Coordinator::startSearchLocation(const QString& locName)
{
    qDebug() << locName;

    if(locName.isEmpty())
    {
        QMessageBox msgBox;//this);
        msgBox.setText("Type location please!");
        msgBox.exec();
        return;
    }
    auto url = MakeGeocodingUrl(locName).toString();

    auto responce = [this](QByteArray&& jsonResp)
    {
        locationVariants = getPlaces(std::move(jsonResp));
        std::vector<QString> content = convertToStringList(locationVariants);
        emit FillLocationList(content);
    };

    downloader->StartDownload(url, responce);
}

unsigned Coordinator::getWidgetId()
{
    auto id = widgetId;
    widgetId++;
    return id;
}

ShortForecastWidget* Coordinator::fillShortForecastWidget(const CurrentWeatherForecast& data)
{
    ShortForecastWidget* shortw =  createForecastWidget(getWidgetId(), data);
    shortw->setMeasureUnit(convertMeasureUnitsToString(appSettings->getMeasureUnit()));
    auto imgTitle = data.icon+".png";
    auto url = MakeWeatherIconUrl(data.icon);
    auto responce = [this, shortw, imgTitle](QByteArray&& jsonResp)
    {
        imageCache->storeImage(imgTitle, std::move(jsonResp));

        auto img = imageCache->getImage(imgTitle);
        if(img && mainWindow->WidgetInShortForecastList(shortw))
            shortw->setForecastIcon(*img);
    };

    emit AddShortForecastWidgetToList(shortw);

    auto img = imageCache->getImage(imgTitle);
    if(!img)
      downloader->StartDownload(url.toString(), responce);
    else
        shortw->setForecastIcon(*img);

    return shortw;
}

void Coordinator::fillDetailForecastWidget(const forecastArray& array)
{
    for(const auto& item: array)
    {
        DetailForecastWidget* detailw = createDetailForecastWidget(item);
        emit FillDetailedForecastList(detailw);
    }
}

void Coordinator::fillFiveDayForecastWidget(const forecastArray& array)
{
    for(const auto& item: array)
    {
        fiveDayForecastWidget* detailw = createFiveDayForecastWidget(item);
        emit FillFiveDayForecastList(detailw);
    }
}

void Coordinator::saveDailyForecast(const GeoData& geodata, const CurrentWeatherForecast& data)
{
    forecastModel->setCurrentForecast(geodata, std::move(data));
}

void Coordinator::saveFiveDaysForecast(const GeoData& geodata, const forecastArray& forecast)
{
    forecastModel->setFiveDayForecast(geodata, forecast);
}

void Coordinator::selectedLocationChanged(unsigned widgetId)
{
    for (auto itFind = dataWidgetIdBindMap.begin(); itFind != dataWidgetIdBindMap.end(); ++itFind)
    {
        if(itFind->second == widgetId)
        {
            emit clearDetailForecastList();

            std::optional<CurrentWeatherForecast> forecast = forecastModel->getCurrentForecast(itFind->first);
            if(!forecast)
                return;
            fillDetailForecastWidget({*forecast});

            break;
        }
    }
}

void Coordinator::deleteAssociatedData(unsigned widgetId)
{
    for (auto itFind = dataWidgetIdBindMap.begin(); itFind != dataWidgetIdBindMap.end(); ++itFind)
    {
        if(itFind->second != widgetId)
            continue;
        forecastModel->deleteStoredLocation(itFind->first);
        dataWidgetIdBindMap.erase(itFind->first);
        break;
    }
}


//https://www.youtube.com/watch?v=ogj3JI57BLM

//https://www.youtube.com/watch?v=gYax47hz1qw&t=327s
//https://www.youtube.com/watch?v=_qbYGyCzrS4
//https://www.youtube.com/watch?v=a5Q7cxw_OBc
