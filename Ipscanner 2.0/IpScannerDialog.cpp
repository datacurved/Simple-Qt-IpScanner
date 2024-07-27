#include "IpScannerDialog.h"
#include "ui_IpScannerDialog.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QDateTime>

IpScannerDialog::IpScannerDialog(QWidget *parent)
    : QWidget(parent), ui(new Ui::IpScannerDialog) {
    ui->setupUi(this);

    // Connect the new find my IP button
    connect(ui->findMyIpButton, &QPushButton::clicked, this, &IpScannerDialog::on_findMyIpButton_clicked);
}

IpScannerDialog::~IpScannerDialog() {
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void IpScannerDialog::on_scanButton_clicked() {
    QString startIp = ui->startIpLineEdit->text();
    QString endIp = ui->endIpLineEdit->text();
    scanResults.clear();  // Clear previous scan results
    ui->outputTextEdit->clear();  // Clear the output text edit
    ui->progressBar->setValue(0);  // Reset the progress bar

    IpScannerWorker *worker = new IpScannerWorker(startIp, endIp);
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::started, worker, &IpScannerWorker::scanIpRange);
    connect(worker, &IpScannerWorker::scanFinished, this, &IpScannerDialog::handleScanFinished);
    connect(worker, &IpScannerWorker::updateProgress, this, &IpScannerDialog::handleUpdateProgress);
    connect(worker, &IpScannerWorker::progressUpdate, this, &IpScannerDialog::handleUpdateProgressBar);
    connect(worker, &IpScannerWorker::scanFinished, worker, &QObject::deleteLater);
    connect(worker, &IpScannerWorker::scanFinished, &workerThread, &QThread::quit);

    workerThread.start();
}

void IpScannerDialog::handleScanFinished(const QVector<QString> &results) {
    scanResults = results;
    ui->outputTextEdit->append("Scan finished.");
}

void IpScannerDialog::handleUpdateProgress(const QString &result) {
    bool filterUnreachable = ui->filterUnreachableRadioButton->isChecked();
    if (filterUnreachable && result.contains("unreachable")) {
        return;
    }
    ui->outputTextEdit->append(result);
}

void IpScannerDialog::handleUpdateProgressBar(int value) {
    ui->progressBar->setValue(value);
}

void IpScannerDialog::on_saveButton_clicked() {
    saveResultsToHtml();
}

void IpScannerDialog::saveResultsToHtml() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as HTML", "", "HTML Files (*.html)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->outputTextEdit->append("Failed to save the file.");
        return;
    }

    QTextStream out(&file);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>IP Scan Results</title>\n</head>\n<body>\n";
    out << "<h1>IP Scan Results</h1>\n";
    out << "<p>Document created on: " << timestamp << "</p>\n";
    out << "<table border=\"1\">\n<tr><th>IP Address</th><th>Status</th><th>MAC Address</th></tr>\n";

    for (const QString &result : scanResults) {
        QStringList parts = result.split(", ");
        QString ip = parts[0].split(" ")[0];
        QString status = parts[0].split(" ")[2];
        QString mac = parts.size() > 1 ? parts[1].split(": ")[1] : "";
        out << QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>\n").arg(ip, status, mac);
    }

    out << "</table>\n</body>\n</html>";

    file.close();
    ui->outputTextEdit->append("Results saved to " + fileName);
}

void IpScannerDialog::on_findMyIpButton_clicked() {
    QString localIp = getLocalIpAddress();
    if (!localIp.isEmpty()) {
        ui->startIpLineEdit->setText(localIp);
        ui->outputTextEdit->append("Local IP found: " + localIp);
    } else {
        ui->outputTextEdit->append("Failed to find local IP.");
    }
}

QString IpScannerDialog::getLocalIpAddress() {
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            return address.toString();
        }
    }
    return QString();
}
