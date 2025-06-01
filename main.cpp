#include "logowanie.h"
#include "mainwindow.h"
#include "czlonkowie_manager.h"
#include <QApplication>

CzlonkowieManager czlonkowieManager;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Logowanie log;
    if (log.exec() == QDialog::Accepted) {
        MainWindow w;
        w.showMaximized();
        return app.exec();
    }
    return 0;
}
