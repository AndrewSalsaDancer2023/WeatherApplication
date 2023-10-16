#pragma once
#include <functional>
#include <map>
#include <memory>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class ContentDownloader : public QObject
{
    Q_OBJECT
public:
    ContentDownloader();
    void StartDownload(const QUrl& address);
    void StartDownload(const QString& address, std::function<void(QByteArray)> callback);
signals:
    void downloadProgress(qint64, qint64);
    void done(const QUrl&, const QByteArray&);
    void error();

private slots:
    void onResult(QNetworkReply* reply);
   // void AddContent(std::vector<std::pair<std::string, std::string>>& vParameters, std::function<void(std::string)> callback);
private:
    std::map<QString, std::function<void(QByteArray)>> handlersMap;
    std::unique_ptr<QNetworkAccessManager> manager;
};
/*
#include <vector>
#include <string>
#include <functional>
class ContentDownloader
{
public:
    ContentDownloader();
    void AddContent(std::vector<std::pair<std::string, std::string>>& vParameters, std::function<void(std::string)> callback);
};
*/

