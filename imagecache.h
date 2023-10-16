#pragma once
#include <QString>
#include <QPixmap>
//#include <QUrl>
#include <QByteArray>
#include <optional>
#include <map>

class ImageCache
{
public:
    explicit ImageCache(const QString& path);
    std::optional<QPixmap> getImage(const QString& name);
    void storeImage(const QString& fileName, const QByteArray& ba);
    void storeFilesInfo();
private:
    void loadFilesInfo();

    QString basePath;
    std::map<QString, QPixmap> cache;
};


