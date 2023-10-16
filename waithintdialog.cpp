#include "waithintdialog.h"
#include "ui_waithintdialog.h"
#include "circularprogresswidget.h"

WaitHintDialog::WaitHintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitHintDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::SplashScreen );
    progressWidget = std::make_unique<TextProgressWidget>(ui->hintLabel, "Wait a minute", 200, this);

    //        TextProgressWidget("Wait a minute", 200, ui->listWidget);
}

WaitHintDialog::~WaitHintDialog()
{
    delete ui;
}
