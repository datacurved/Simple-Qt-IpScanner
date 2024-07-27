#ifndef IPSCANNERDIALOG_H
#define IPSCANNERDIALOG_H

#include <QWidget>
#include <QVector>
#include <QThread>
#include "IpScannerWorker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IpScannerDialog; }
QT_END_NAMESPACE

class IpScannerDialog : public QWidget {
    Q_OBJECT

public:
    explicit IpScannerDialog(QWidget *parent = nullptr);
    ~IpScannerDialog();

private slots:
    void on_scanButton_clicked();
    void on_saveButton_clicked();
    void on_findMyIpButton_clicked();
    void handleScanFinished(const QVector<QString> &results);
    void handleUpdateProgress(const QString &result);
    void handleUpdateProgressBar(int value);

private:
    Ui::IpScannerDialog *ui;
    QVector<QString> scanResults;
    QThread workerThread;

    void saveResultsToHtml();
    QString getLocalIpAddress();
};

#endif // IPSCANNERDIALOG_H
