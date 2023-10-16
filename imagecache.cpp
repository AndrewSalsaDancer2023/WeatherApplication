#include "imagecache.h"
#include <QFile>
#include <QThreadPool>
#include <QStandardPaths>
#include <QRunnable>
#include <QPixmap>
#include <QJsonArray>
#include <QSettings>
#include <QJsonDocument>
#include <QStringList>

ImageCache::ImageCache(const QString& path)
{
    loadFilesInfo();
    if(basePath.isEmpty())
        basePath = path;
}

std::optional<QPixmap> ImageCache::getImage(const QString& name)
{
    auto it = cache.find(name);
    if(it != cache.end())
        return it->second;
/*
    QString strFileName = basePath+"/"+name;
    if(!QFile::exists(strFileName))
        return std::nullopt;

    QPixmap pixmap;
    if(!pixmap.load(strFileName))
        return std::nullopt;

    cache[name] = pixmap;
    return pixmap;
*/
    return std::nullopt;
}

class SaveFileTask : public QRunnable
{
    void run()
    {
        QFile file(filepath);
        if(!file.open(QIODevice::WriteOnly))
            return;

         content.save(&file, "PNG");
    }    

public:
   SaveFileTask(const QString& path, const QPixmap& img)
     :filepath{path}, content{img}//content{data}
 {
 }
private:
    const QString filepath;
    const QPixmap& content;
};

void ImageCache::storeImage(const QString& fileName,const QByteArray& ba)
{
    QPixmap pixmap;
    if(!pixmap.loadFromData(ba))
        return;

//    QString pictUrl = url.path().section('/', -1);
//    cache[pictUrl] = pixmap;
    cache[fileName] = std::move(pixmap);

    //save in different thread
    QString strFileName = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/"+fileName;//url.path().section('/', -1);
   // SaveFileTask *saveTask = new SaveFileTask(strFileName, ba);
    SaveFileTask *saveTask = new SaveFileTask(strFileName, cache[fileName]);
    // QThreadPool takes ownership and deletes 'hello' automatically
    QThreadPool::globalInstance()->start(saveTask);
}


void ImageCache::storeFilesInfo()
{
    QStringList fileList;
    for (auto itr = cache.begin(); itr !=cache.end(); ++itr) {
         fileList << itr->first;
     }

     QJsonArray array = QJsonArray::fromStringList(fileList);
     QJsonDocument doc{array};
     QString content{doc.toJson()};

     QSettings settings{"DSS", "WeatherApp"};
     settings.setValue("filenames", content);
     settings.setValue("path", basePath);
}

void ImageCache::loadFilesInfo()
{
    QSettings settings{"DSS", "WeatherApp"};
    basePath = settings.value("path").toString();

    QString namesArray = settings.value("filenames").toString();
    QJsonDocument doc = QJsonDocument::fromJson(namesArray.toUtf8());
    if(!doc.isArray())
        return;

    QJsonArray arr = doc.array();
    for(int i = 0; i < arr.count(); ++i)
    {
        QString fileName = arr.at(i).toString();
        QString strFilePath = basePath+"/"+fileName;

        QPixmap pixmap;
        if(pixmap.load(strFilePath))
            cache[fileName] = pixmap;
    }
}
