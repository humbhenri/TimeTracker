#include "timetrackerapp.h"
#define ORG_NAME "HumbertoApps"
#define APP_NAME "TimeTracker"

TimeTrackerApp::TimeTrackerApp(int & argc, char** argv) :
    QApplication(argc, argv)
{
    setOrganizationName(ORG_NAME);
    setApplicationName(APP_NAME);

    mainWindow = new MainWindow();
    mainWindow->show();

}

TimeTrackerApp::~TimeTrackerApp()
{
    delete mainWindow;
}
