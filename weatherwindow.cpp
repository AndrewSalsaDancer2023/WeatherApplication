#include "weatherwindow.h"
#include "ui_weatherwindow.h"
#include "shortforecastwidget.h"
#include "detailforecastwidget.h"
#include "fivedayforecastwidget.h"
#include "geocoder.h"
#include <QPixmap>
#include "coordinator.h"
#include "taskprocessor.h"
#include "contentdownloader.h"
#include "geocodingparameters.h"
#include "contentdownloader.h"
#include "utilities.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

WeatherWindow::WeatherWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherWindow)
{
    ui->setupUi(this);
    connect(ui->shortForecastWidget, SIGNAL(itemSelectionChanged()), this, SLOT(shortForecastWidgetSelectionChanged())) ;

}

WeatherWindow::~WeatherWindow()
{
    delete ui;
}

void WeatherWindow::shortForecastWidgetSelectionChanged()
{
    QList<QListWidgetItem *> selected =  ui->shortForecastWidget->selectedItems();
    if(selected.isEmpty())
        return;
    QListWidgetItem *pItem = selected.takeFirst();
    on_shortForecastWidget_itemClicked(pItem);
}

void WeatherWindow::AddShortForecastWidgetToList(ShortForecastWidget* widget)
{
    if(!widget)
        return;

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());

    ui->shortForecastWidget->addItem(item);
    ui->shortForecastWidget->setItemWidget(item, widget);
}

unsigned WeatherWindow::getNumItemsInDetailedForecastList()
{
    return ui->detailedForecastWidget->count();
}

void WeatherWindow::FillDetailedForecastList(DetailForecastWidget* widget)
{
    if(!widget)// || ui->detailedForecastWidget->count())
        return;

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());

    ui->detailedForecastWidget->addItem(item);
    ui->detailedForecastWidget->setItemWidget(item, widget);
}

void WeatherWindow::FillFiveDayForecastList(fiveDayForecastWidget* widget)
{
    if(!widget)// || ui->detailedForecastWidget->count())
        return;

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());

    ui->detailedForecastWidget->addItem(item);
    ui->detailedForecastWidget->setItemWidget(item, widget);
}

void WeatherWindow::FillForecastList()
{
    ui->shortForecastWidget->clear();

}

void WeatherWindow::AddLocationClicked()
{
    emit showAddLocationDialog();
 }

void WeatherWindow::on_actionAdd_location_triggered()
{
    AddLocationClicked();
}

void WeatherWindow::on_actionDelete_location_triggered()
{
    QList<QListWidgetItem *> selected =  ui->shortForecastWidget->selectedItems();

    while(!selected.isEmpty())
    {
        QListWidgetItem *pItem = selected.takeFirst();
        QWidget *pItemWidget = ui->shortForecastWidget->itemWidget(pItem);
        ShortForecastWidget* forecastWidget = dynamic_cast<ShortForecastWidget *>(pItemWidget);
        if(forecastWidget)
            emit deleteAssociatedData(forecastWidget->getWidgetId());
        delete pItem;
    }

}

void readResponce(std::string resp)
{
    int k = 10;
    qDebug() << QString::fromStdString(resp);
}

void WeatherWindow::deleteWidgetFromList(QListWidget* pList, int row)
{
    if(!pList || (pList->count() <= row))
        return;

    QListWidgetItem *pItem = pList->takeItem(row);
    delete pItem;
}


void WeatherWindow::deleteWidgetsFromDetailForecastList()
{
    auto count = ui->detailedForecastWidget->count();

    for(int row = 0; row < count; ++row)
    {
        QListWidgetItem *pItem = ui->detailedForecastWidget->takeItem(0);
        delete pItem;
    }
    count = ui->detailedForecastWidget->count();
    qDebug() << count;
}

ShortForecastWidget* WeatherWindow::getShortForecastWidget(unsigned widgetId)
{
    for(int row = 0; row < ui->shortForecastWidget->count(); ++row)
    {
        QListWidgetItem *pItem = ui->shortForecastWidget->item(row);
        QWidget *pItemWidget = ui->shortForecastWidget->itemWidget(pItem);
        ShortForecastWidget* forecastWidget = dynamic_cast<ShortForecastWidget *>(pItemWidget);
        if(forecastWidget && forecastWidget->getWidgetId() == widgetId)
            return forecastWidget;
    }

    return nullptr;
}

bool WeatherWindow::WidgetInShortForecastList(ShortForecastWidget* widget)
{
    for(int row = 0; row < ui->shortForecastWidget->count(); ++row)
    {
        QListWidgetItem *pItem = ui->shortForecastWidget->item(row);
        QWidget *pItemWidget = ui->shortForecastWidget->itemWidget(pItem);
        ShortForecastWidget* forecastWidget = dynamic_cast<ShortForecastWidget *>(pItemWidget);
        if(forecastWidget == widget)
            return true;
    }

    return false;
}

void WeatherWindow::on_actionQuit_triggered()
{
    emit quitApp();
}

void WeatherWindow::on_actionSettings_triggered()
{
    emit showSettingsDialog();
}


//https://www.gollahalli.com/blog/2021/1/creating-custom-widget-for-qlistwidget-in-qt-6/
//https://www.youtube.com/watch?v=8mCSDR1NpoU&list=PL3BR09unfgcgf7R88ZQRQqWOdLy4pRW2h&index=11
//https://www.youtube.com/watch?v=yZsWgufydCU
//https://habr.com/ru/companies/wunderfund/articles/582000/
//https://www.youtube.com/@qtwithketan/playlists
//https://books.google.ru/books?id=ttnPEAAAQBAJ&pg=PT1255&lpg=PT1255&dq=IFNDR+c%2B%2B&source=bl&ots=crDeCj9YrT&sig=ACfU3U2wzauqlRnTI3dAq_woCB33bA5AIA&hl=en&sa=X&ved=2ahUKEwjSsqy5rOGAAxUklosKHY3cAwUQ6AF6BAg3EAM#v=onepage&q=IFNDR%20c%2B%2B&f=false
//https://habr.com/ru/articles/271203/
//https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio/examples/cpp11_examples.html
//https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio/example/cpp11/chat/chat_client.cpp
//https://www.flaticon.com/search?word=plus%20sign&color=color

//Григорий Демченко | Асинхронность и неблокирующая синхронизация
//https://www.youtube.com/watch?v=XWi8WNM4PHQ
//Павел Новиков — Асинхронная разработка на C++
//https://www.youtube.com/watch?v=seDJT66BJJo https://www.youtube.com/watch?v=seDJT66BJJo&t=2144s
//Eric Niebler — A unifying abstraction for async in C++
//https://www.youtube.com/watch?v=h-ExnuD6jms&t=1s
//Thiago Macieira: Qt event loop, networking and I/O API
//https://www.youtube.com/watch?v=oKXDY90OCj0

void WeatherWindow::on_shortForecastWidget_itemClicked(QListWidgetItem *item)
{
    QWidget *pItemWidget = ui->shortForecastWidget->itemWidget(item);
    ShortForecastWidget* forecastWidget = dynamic_cast<ShortForecastWidget *>(pItemWidget);
    if(!forecastWidget)
        return;
//    qDebug() << "widget serlected:" << forecastWidget->getWidgetId() <<"\n";
    emit locationSelected(forecastWidget->getWidgetId());
}
