#ifndef ADDLOCATIONDIALOG_H
#define ADDLOCATIONDIALOG_H
#include <QDialog>
#include <QTimer>
#include <memory>
#include <optional>

namespace Ui {
class AddLocationDialog;

}
class QListWidgetItem;
class WaitHintDialog;
class ContentDownloader;

class AddLocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocationDialog(QWidget *parent = nullptr);
    ~AddLocationDialog();
    std::optional<QString> getSelectedPlaceTitle();
    QString getSearchedLocation();
public slots:
    void startSearch();
    void timerExpired();
    void FillLocationList(const std::vector<QString>& locNames);
//    void locationSelected(QListWidgetItem *pWidget);
signals:
    void startSearchLocation(const QString&);
    void waitingFinished();
//private:
//    void FillLocationList(const std::vector<QString>& locNames);
private:
    Ui::AddLocationDialog *ui;
    std::unique_ptr<WaitHintDialog> waitDlg;
    std::unique_ptr<ContentDownloader> downloader;
};

#endif // ADDLOCATIONDIALOG_H
