#include "forecastsettings.h"
#include <map>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QSettings>
#include <QJsonArray>
#include <QJsonObject>

std::map<QString, QString> langNameCodes = {
    {"English", "en"},
    {"Russian", "ru"},
    {"Afrikaans", "af"},
    {"Arabic", "ar"},
    {"Bulgarian", "bg"},
    {"Czech", "cz"},
    {"Danish", "da"},
    {"German", "de"},
    {"Greek", "el"},
    {"French", "fr"},
    {"Hindi", "hi"},
    {"Italian", "it"},
    {"Japanese", "ja"},
    {"Korean", "kr"},
    {"Portuguese", "pt"},
    {"Chinese Simplified", "zh_cn"},
    {"Chinese Traditional", "zh_tw"}
};

ForecastSettings::ForecastSettings(ForecastTypes type, MeasureUnits unit, const QString& language)
    :  forecastType{type}, measureUnit{unit}, curLanguage{language}
{}

 QString ForecastSettings::getLanguageCode()
 {
    auto itFind = langNameCodes.find(curLanguage);
    if(itFind != langNameCodes.end())
        return itFind->second;

    return "en";
 }

 QList<QString> ForecastSettings::getLanguageList()
 {
     QList<QString> result;
     for(const auto& langPair: langNameCodes)
         result.append(langPair.first);

     return result;
 }

 void ForecastSettings::saveSettings()
 {
    QJsonObject jobject;

    jobject["language"] = curLanguage;
    jobject["forecastType"] = static_cast<int>(forecastType);
    jobject["measureUnits"] = static_cast<int>(measureUnit);

    QJsonArray array;
    array.push_back(jobject);

    QJsonDocument doc{array};
    QString content{doc.toJson()};

    QSettings settings{"DSS", "WeatherApp"};
    settings.setValue("preferences", content);
 }

 void ForecastSettings::restoreSettings()
 {
     QSettings settings{"DSS", "WeatherApp"};
     QString content = settings.value("preferences").toString();
//     qDebug() << content;
     QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
     if(!doc.isArray())
         return;

     QJsonArray arr = doc.array();
     if(arr.empty())
         return;

     QJsonObject jobject = arr.at(0).toObject();
     curLanguage = jobject["language"].toString();
     forecastType = static_cast<ForecastTypes>(jobject["forecastType"].toInt());
     measureUnit = static_cast<MeasureUnits>(jobject["measureUnits"].toInt());
 }


 QString ForecastSettings::getMeasureUnitAsString()
 {
     QString result;
     switch(measureUnit)
     {
        case MeasureUnits::standard:
         result = "standard";
         break;
        case MeasureUnits::metric:
         result = "metric";
         break;
        default:
         result = "imperial";
     }
    return result;
 }

//https://www.youtube.com/watch?v=Hywp-92uvfo
//https://www.youtube.com/playlist?list=PL4_hYwCyhAvYn9QJJUb1WjHuhG3ojyuHL
