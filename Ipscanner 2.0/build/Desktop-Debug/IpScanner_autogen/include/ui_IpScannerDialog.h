/********************************************************************************
** Form generated from reading UI file 'IpScannerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPSCANNERDIALOG_H
#define UI_IPSCANNERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IpScannerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *startIpLineEdit;
    QLineEdit *endIpLineEdit;
    QPushButton *findMyIpButton;
    QPushButton *scanButton;
    QPushButton *saveButton;
    QRadioButton *filterUnreachableRadioButton;
    QProgressBar *progressBar;
    QTextEdit *outputTextEdit;

    void setupUi(QWidget *IpScannerDialog)
    {
        if (IpScannerDialog->objectName().isEmpty())
            IpScannerDialog->setObjectName("IpScannerDialog");
        IpScannerDialog->resize(400, 400);
        verticalLayout = new QVBoxLayout(IpScannerDialog);
        verticalLayout->setObjectName("verticalLayout");
        startIpLineEdit = new QLineEdit(IpScannerDialog);
        startIpLineEdit->setObjectName("startIpLineEdit");

        verticalLayout->addWidget(startIpLineEdit);

        endIpLineEdit = new QLineEdit(IpScannerDialog);
        endIpLineEdit->setObjectName("endIpLineEdit");

        verticalLayout->addWidget(endIpLineEdit);

        findMyIpButton = new QPushButton(IpScannerDialog);
        findMyIpButton->setObjectName("findMyIpButton");

        verticalLayout->addWidget(findMyIpButton);

        scanButton = new QPushButton(IpScannerDialog);
        scanButton->setObjectName("scanButton");

        verticalLayout->addWidget(scanButton);

        saveButton = new QPushButton(IpScannerDialog);
        saveButton->setObjectName("saveButton");

        verticalLayout->addWidget(saveButton);

        filterUnreachableRadioButton = new QRadioButton(IpScannerDialog);
        filterUnreachableRadioButton->setObjectName("filterUnreachableRadioButton");

        verticalLayout->addWidget(filterUnreachableRadioButton);

        progressBar = new QProgressBar(IpScannerDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        outputTextEdit = new QTextEdit(IpScannerDialog);
        outputTextEdit->setObjectName("outputTextEdit");

        verticalLayout->addWidget(outputTextEdit);


        retranslateUi(IpScannerDialog);

        QMetaObject::connectSlotsByName(IpScannerDialog);
    } // setupUi

    void retranslateUi(QWidget *IpScannerDialog)
    {
        IpScannerDialog->setWindowTitle(QCoreApplication::translate("IpScannerDialog", "IP Scanner", nullptr));
        startIpLineEdit->setPlaceholderText(QCoreApplication::translate("IpScannerDialog", "Start IP", nullptr));
        endIpLineEdit->setPlaceholderText(QCoreApplication::translate("IpScannerDialog", "End IP", nullptr));
        findMyIpButton->setText(QCoreApplication::translate("IpScannerDialog", "Find My IP", nullptr));
        scanButton->setText(QCoreApplication::translate("IpScannerDialog", "Scan", nullptr));
        saveButton->setText(QCoreApplication::translate("IpScannerDialog", "Save to HTML", nullptr));
        filterUnreachableRadioButton->setText(QCoreApplication::translate("IpScannerDialog", "Filter Unreachable Addresses", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IpScannerDialog: public Ui_IpScannerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPSCANNERDIALOG_H
