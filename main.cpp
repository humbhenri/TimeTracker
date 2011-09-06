#include <QtGui/QApplication>
#include "mainwindow.h"

#define ORG_NAME "HumbertoApps"
#define APP_NAME "TimeTracker"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(ORG_NAME);
    a.setApplicationName(APP_NAME);
    MainWindow w;
    w.show();

    return a.exec();
}
