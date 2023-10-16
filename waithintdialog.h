#ifndef WAITHINTDIALOG_H
#define WAITHINTDIALOG_H
#include "waithintdialog.h"
#include <memory>
#include <QDialog>

namespace Ui {
class WaitHintDialog;
}

class TextProgressWidget;

class WaitHintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitHintDialog(QWidget *parent = nullptr);
    ~WaitHintDialog();

private:
    std::unique_ptr<TextProgressWidget> progressWidget;
    Ui::WaitHintDialog *ui;
};

#endif // WAITHINTDIALOG_H
