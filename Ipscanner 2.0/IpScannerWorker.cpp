#include "IpScannerWorker.h"
#include <QProcess>
#include <QRegularExpression>
#include <QThreadPool>
#include <QtConcurrent>

IpScannerWorker::IpScannerWorker(const QString &startIp, const QString &endIp, QObject *parent)
    : QObject(parent), startIp(startIp), endIp(endIp) {}

void IpScannerWorker::scanIpRange() {
    QVector<QString> scanResults;
    QRegularExpression ipRegex("^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$");
    QRegularExpressionMatch startMatch = ipRegex.match(startIp);
    QRegularExpressionMatch endMatch = ipRegex.match(endIp);

    if (!startMatch.hasMatch() || !endMatch.hasMatch()) {
        emit updateProgress("Invalid IP format.");
        return;
    }

    int startParts[4];
    int endParts[4];

    for (int i = 0; i < 4; ++i) {
        startParts[i] = startMatch.captured(i + 1).toInt();
        endParts[i] = endMatch.captured(i + 1).toInt();
    }

    int totalIps = endParts[3] - startParts[3] + 1;
    int processedIps = 0;

    QThreadPool pool;
    pool.setMaxThreadCount(10);

    for (int i = startParts[3]; i <= endParts[3]; ++i) {
        QString ip = QString("%1.%2.%3.%4").arg(startParts[0]).arg(startParts[1]).arg(startParts[2]).arg(i);

        auto scanTask = [this, ip, &scanResults, &processedIps, totalIps]() {
            QProcess pingProcess;
            pingProcess.start("ping", QStringList() << "-c" << "1" << "-W" << "1" << ip);
            pingProcess.waitForFinished();

            QString result;
            QString macAddress = resolveMacAddress(ip);
            if (pingProcess.exitCode() == 0) {
                result = QString("%1 is reachable, MAC: %2").arg(ip, macAddress);
            } else {
                result = QString("%1 is unreachable").arg(ip);
            }

            scanResults.append(result);
            emit updateProgress(result);

            processedIps++;
            int progress = static_cast<int>((processedIps / static_cast<double>(totalIps)) * 100);
            emit progressUpdate(progress);
        };

        QtConcurrent::run(&pool, scanTask);
    }

    pool.waitForDone();
    emit scanFinished(scanResults);
}

QString IpScannerWorker::resolveMacAddress(const QString &ipAddress) {
    QProcess arpProcess;
    arpProcess.start("arp", QStringList() << "-n" << ipAddress);
    arpProcess.waitForFinished();

    QString output = arpProcess.readAllStandardOutput();
    QRegularExpression macRegex("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})");
    QRegularExpressionMatch macMatch = macRegex.match(output);

    if (macMatch.hasMatch()) {
        return macMatch.captured(0);
    }

    return "Unknown";
}
