#include "timetrackerapp.h"
#define ORG_NAME "HumbertoApps"
#define APP_NAME "TimeTracker"
#define DB_NAME "timetracker.sqlite"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QDesktopWidget>

TimeTrackerApp::TimeTrackerApp(int & argc, char** argv) :
    QApplication(argc, argv)
{
    setOrganizationName(ORG_NAME);
    setApplicationName(APP_NAME);

    initDB();

    mainWindow = new MainWindow();
    QRect frect = mainWindow->frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    mainWindow->move(frect.topLeft());
    mainWindow->show();

}

TimeTrackerApp::~TimeTrackerApp()
{    
    delete mainWindow;
    closeDB();
}

void TimeTrackerApp::initDB()
{
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query("create table project(id integer primary key, name text, description text, created text, lastModified text)");
    QSqlQuery query2("create table timespan(id integer primary key, start text, end text, projectId integer, FOREIGN KEY(projectId) REFERENCES project(id))");
}

void TimeTrackerApp::closeDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}
