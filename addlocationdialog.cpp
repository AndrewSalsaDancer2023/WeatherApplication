#include "addlocationdialog.h"
#include "ui_addlocationdialog.h"
#include "circularprogresswidget.h"
#include <QListWidget>
#include <QDebug>
#include "waithintdialog.h"
#include <memory>
#include <QMessageBox>
#include "geocodingparameters.h"
#include "settingstore.h"
//#include "geocoder.h"
#include "contentdownloader.h"
//#include "utilities.h"
#include <QUrl>

AddLocationDialog::AddLocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLocationDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::SplashScreen );
    connect(ui->okCancelBtnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->okCancelBtnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(startSearch()));
    //connect(ui->locListWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(locationSelected(QListWidgetItem *)));

    ui->searchText->setFocus(Qt::OtherFocusReason);

    //TextProgressWidget *pWidg = new TextProgressWidget("Wait a minute", 200, ui->listWidget);
    //pWidg->show();


    //ui->hintLayout->setSizeHint(pWidg->sizeHint());
    //ui->hintLayout->addWidget(pWidg);
    //ui->hintLayout->addItem(pWidg);

 //    ui->listWidget->addItem(item);
 //    ui->listWidget->setItemWidget(item, widget);
    //pWidg->show();
    downloader = std::make_unique<ContentDownloader>();
}

void AddLocationDialog::FillLocationList(const std::vector<QString>& locNames)
{
    ui->locListWidget->clear();
    for(const auto& name: locNames )
        ui->locListWidget->addItem(name);

    if(ui->locListWidget->count())
        ui->locListWidget->setCurrentRow(0);
    else
        ui->locListWidget->addItem("No place found. Please try correct name");
}

QString AddLocationDialog::getSearchedLocation()
{
    return ui->searchText->text();
}

void AddLocationDialog::startSearch()
{
    auto location = ui->searchText->text();
    emit startSearchLocation(location);
}

/*
    waitDlg = std::make_unique<WaitHintDialog>(this);
    QTimer::singleShot(3000, this, SLOT(timerExpired()));
    waitDlg->exec();
*/

void AddLocationDialog::timerExpired()
{
    if(waitDlg)
        waitDlg->accept();
}

AddLocationDialog::~AddLocationDialog()
{
    delete ui;
}

std::optional<QString> AddLocationDialog::getSelectedPlaceTitle()
{
  if(!ui->locListWidget->count())
      return std::nullopt;

  return ui->locListWidget->currentItem()->text();
}


//https://stackoverflow.com/questions/42793906/custom-circular-progressbar-in-qt
//https://wiki.qt.io/QWidget_Semi-transparent_Background_Color
