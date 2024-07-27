#ifndef IPSCANNERWORKER_H
#define IPSCANNERWORKER_H

#include <QObject>
#include <QString>
#include <QVector>

class IpScannerWorker : public QObject {
    Q_OBJECT

public:
    explicit IpScannerWorker(const QString &startIp, const QString &endIp, QObject *parent = nullptr);

signals:
    void scanFinished(const QVector<QString> &results);
    void updateProgress(const QString &result);
    void progressUpdate(int value);

public slots:
    void scanIpRange();

private:
    QString startIp;
    QString endIp;

    QString resolveMacAddress(const QString &ipAddress);
};

#endif // IPSCANNERWORKER_H
