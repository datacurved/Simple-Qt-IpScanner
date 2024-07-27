#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ipScannerDialog(new IpScannerDialog(this)) {
    setCentralWidget(ipScannerDialog);
    setWindowTitle("IP Scanner");
}

MainWindow::~MainWindow() {
    delete ipScannerDialog;
}
