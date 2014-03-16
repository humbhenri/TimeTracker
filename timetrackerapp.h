#ifndef TIMETRACKERAPP_H
#define TIMETRACKERAPP_H

#include <QtWidgets>
#include <QApplication>
#include "mainwindow.h"

class TimeTrackerApp : public QApplication
{
    Q_OBJECT
public:
    explicit TimeTrackerApp(int & argc, char** argv);
    virtual ~TimeTrackerApp();
    void initDB();
    void closeDB();

private:
    MainWindow* mainWindow;
signals:

public slots:

};

#endif // TIMETRACKERAPP_H
