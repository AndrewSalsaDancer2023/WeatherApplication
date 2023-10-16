#include "contentdownloader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>

ContentDownloader::ContentDownloader()
{
   manager = std::make_unique<QNetworkAccessManager>();
   connect(manager.get(), &QNetworkAccessManager::finished, this, &ContentDownloader::onResult);
}

void ContentDownloader::StartDownload(const QString& address, std::function<void(QByteArray)> callback)
{
    if(handlersMap.find(address) == handlersMap.end())
        handlersMap[address] = callback;
    manager->get(QNetworkRequest(QUrl(address)));
}

void ContentDownloader::StartDownload(const QUrl& address)
{
    manager->get(QNetworkRequest(address));
}

void ContentDownloader::onResult(QNetworkReply* reply)
{
//    qDebug() << "recieve answer from:" << reply->url().toString() << "\n";
    if(!reply->error())
    {
        auto query = reply->url().toString();
        auto it = handlersMap.find(query);
        if(it != handlersMap.end())
        {
            it->second(std::move(reply->readAll()));
            handlersMap.erase(it);
        }
            //handlersMap[query](std::move(reply->readAll()));
    }
//    else {
//        qDebug() << "error downloading:" << reply->url().toString() << "\n";
//    }
    reply->deleteLater();
}
/*
#include "asyncdownloader.h"
#include <boost/asio/io_context.hpp>
#include <thread>
#include <memory>

ContentDownloader::ContentDownloader()
{

}

void ContentDownloader::AddContent(std::vector<std::pair<std::string, std::string>>& vParameters,
                                   std::function<void(std::string)> callback)
{
    auto downloadContent = [parameters = std::move(vParameters), callback]() {
         const char *defaultPort = "80";
         const int defaultProtocolVersion = 11;

        boost::asio::io_context ioc;
        std::vector<std::shared_ptr<asyncDownloader>> loaders;
        for(const auto& params : parameters)
        {

           std::shared_ptr<asyncDownloader> loader = std::make_shared<asyncDownloader>(ioc);
           loaders.push_back(std::move(loader));
           loaders.back()->run(params.first.c_str(), defaultPort,
                                                    params.second.c_str(), defaultProtocolVersion,
                                                    callback);
        }

        ioc.run();
    };

    std::thread downloader(downloadContent);
    downloader.detach();

}
*/
