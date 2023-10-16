//#include "weatherwindow.h"
#include "coordinator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto coordinator = std::make_shared<Coordinator>(a);
    coordinator->ShowMainWindow();
    coordinator->FillShortForecastList();

    return a.exec();
}
//https://www.youtube.com/watch?v=UjISpCKGAuo
//https://www.youtube.com/watch?v=6JMXP7ZqHcw
//https://www.youtube.com/watch?v=bpMgQea0OUc
//https://doc.qt.io/qt-5/resources.html

//mongodb
//https://www.mongodb.com/community/forums/t/installation-of-mongodb-on-ubuntu-22-04/198860/5
//https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/
//https://www.mongodb.com/community/forums/t/installing-mongodb-over-ubuntu-22-04/159931/17
//https://tecadmin.net/how-to-install-mongodb-on-ubuntu-22-04/

//playmongo https://www.youtube.com/watch?v=GtD93tVZDX4&list=PLS1QulWo1RIZtR6bncmSaH8fB81oRl6MP

//qt from sources
//https://doc.qt.io/qt-6/configure-options.html
//https://doc.qt.io/qt-6/macos.html#build-environment
//https://doc.qt.io/qt-6/macos-building.html
//https://doc.qt.io/qt-6/build-sources.html
//https://wiki.qt.io/Building_Qt_5_from_Git
//https://doc.qt.io/qt-6/linux-building.html

//асинхронность c++
//https://forum.qt.io/topic/77586/is-this-an-acceptable-safe-way-to-update-gui-from-another-thread/7
//https://www.youtube.com/watch?v=NfHoOavesHE
//https://habr.com/ru/articles/271203/
//https://habr.com/ru/companies/wunderfund/articles/582000/
//https://www.youtube.com/watch?v=KmhueUsqUwY
//https://www.boost.org/doc/libs/1_82_0/libs/beast/doc/html/index.html
//https://www.boost.org/doc/libs/1_83_0/libs/beast/doc/html/beast/quick_start/http_client.html
//https://www.boost.org/doc/libs/1_83_0/libs/beast/example/http/client/async/http_client_async.cpp
//https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio/examples.html
//https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio/tutorial/tutdaytime3.html
//https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio/tutorial.html
//https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html

//https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#SScp-par

//qt gui
//https://www.youtube.com/watch?v=vde95l737PI&list=PLYf4Vz9V1ESrVD_NMDlwRjgo8jn2UNEND
//https://www.youtube.com/watch?v=44IbJnTiKRg
//https://www.youtube.com/watch?v=lTJ-QkC_Sxw
//https://www.youtube.com/watch?v=tvpC8UrPpZ4
//https://www.youtube.com/watch?v=PR6wVy7Et1A
//https://www.youtube.com/watch?v=PR6wVy7Et1A

//std::multithreading
//https://habr.com/ru/articles/182610/
//https://habr.com/ru/articles/182626/

//chat app
//https://www.pixelcrayons.com/blog/messaging-application-development/
//https://habr.com/ru/articles/683898/

//https://www.google.com/search?q=chat+mongodb+design&oq=chat+mongodb&aqs=chrome.3.69i57j0i22i30l8j0i15i22i30.8527j1j7&sourceid=chrome&ie=UTF-8#ip=1
//https://www.youtube.com/watch?v=GAt-XjGvMxM
//https://www.youtube.com/watch?v=mhUQe4BKZXs&list=PLkQkbY7JNJuBoTemzQfjym0sqbOHt5fnV
//https://www.youtube.com/watch?v=Nt_gWiPMzNM
//https://www.youtube.com/watch?v=xL_tYrEcP9M
//http://www.mongodb.org/display/DOCS/Schema+Design
//http://docs.mongodb.org/manual/use-cases/storing-comments/
//https://www.mongodb.com/community/forums/t/advice-for-chat-schema-design/114166/16
//https://dba.stackexchange.com/questions/306757/chat-schema-for-postgresql-and-mongodb
//https://www.mongodb.com/developer/code-examples/swift/realm-swiftui-ios-chat-app/
//https://www.exoplatform.com/blog/exo-platform-chat-application-why-mongodb-team-collaboration-software/

//mongo compile
//https://mongocxx.org/mongocxx-v3/installation/linux/
//http://mongoc.org/libmongoc/current/installing.html
//https://mongocxx.org/
//https://mongocxx.org/mongocxx-v3/tutorial/
//https://www.youtube.com/watch?v=NC7IGLm69Ts
//mongo doc: https://www.mongodb.com/basics https://www.w3schools.com/mongodb/mongodb_drivers.php
//https://www.w3schools.com/mongodb/index.php

//websockets
//https://www.youtube.com/watch?v=ZSefPfZqxpo
//https://www.youtube.com/watch?v=rK7-_h8OQ2M
//https://www.youtube.com/watch?v=_vAjHdh92YU
//secured network protocols https://www.youtube.com/watch?v=LTLqazCztnc&list=PLtPJ9lKvJ4oiFnWCsVRElorOLt69YDEnv
//linux admin https://www.youtube.com/playlist?list=PL0LmdiLYQ3Y_MZC48T7ha2MgIlrLuAfYP
//testing https://www.youtube.com/watch?v=j5w2J68jPd4
//https://www.youtube.com/results?search_query=C%2B%2B+Websocket+Introduction+with+Boost+library+Part
//https://bbbbyang.github.io/2019/09/28/TLS-and-Boost-websocket/
//https://think-async.com/Asio/boost_asio_1_18_0/doc/html/boost_asio/overview/ssl.html

//https://coderprog.com/accelerating-server-side-development-fastify/
//https://www.youtube.com/watch?v=UjISpCKGAuo&t=8s
//

//qt mvc
//https://www.youtube.com/watch?v=GMbSh6-cwD4
//
