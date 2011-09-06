#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QCheckBox>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include "preferenceswidget.h"
#include "preferences.h"
#include "trayiconcommand.h"
#include "projectwidget.h"
#include "timespan.h"
#include "project.h"
#include "screenshot.h"

#define NORMAL_CLOCK_ICON ":/res/images/clock.png"
#define OFF_CLOCK_ICON ":/res/images/clock-off.png"
#define TRACKING_ON "Stop"
#define TRACKING_OFF "Start"
#define WINDOW_ICON NORMAL_CLOCK_ICON
#define PAYPAL_URL "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=VXJX2VJMQKLG2"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    screenShotTimer(this),
    isTracking(false),
    isTakingScreenShots(false)
{    
    preferences = new Preferences;
    createCommands();
    preferences->loadPreferences();

    ui->setupUi(this);

    setWindowIcon(QIcon(WINDOW_ICON));

    prefWidget = ui->centralWidget->findChild<PreferencesWidget*>("preferencesWidget");
    prefWidget->setModel(preferences);

    createActions();

    createTrayIcon();

    makeConnections();

    trayIcon->show();

    trackBeginning = QDateTime::currentDateTime();
}

MainWindow::~MainWindow()
{
    if (isTracking)
        stopClock();
    preferences->savePreferences();
    delete ui;
    delete trayIcon;
    delete trayIconMenu;
    delete preferences;
    commands->clear();
    delete commands;
    delete minimizeAction;
    delete restoreAction;
    delete quitAction;
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
     if (trayIcon->isVisible()) {
         QMessageBox::information(this, tr("Systray"),
                                  tr("The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
         hide();
         event->ignore();
     }
 }

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    toggleAction = new QAction(tr("&Toggle Tracking"), this);
    connect(toggleAction, SIGNAL(triggered()), this, SLOT(toggleTracking()));

}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(toggleAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(OFF_CLOCK_ICON));
    trayIcon->setToolTip(isTracking ? TRACKING_ON : TRACKING_OFF);

}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        preferences->getSingleClick()->execute();
        break;
    case QSystemTrayIcon::DoubleClick:
        preferences->getDoubleClick()->execute();
        break;
    default:
        ;
    }
}

/**
  * Save preferences changes made by the user
  */
void MainWindow::savePreferences()
{
    QComboBox *singleClickCombo = ui->centralWidget->findChild<QComboBox*>("traySingleComboBox");
    QComboBox *doubleClickCombo = ui->centralWidget->findChild<QComboBox*>("trayDoubleComboBox");

    QString singleClick = singleClickCombo->currentText();
    QString doubleClick = doubleClickCombo->currentText();

    preferences->setSingleClick(singleClick);
    preferences->setDoubleClick(doubleClick);

}

void MainWindow::makeConnections() {
    QPushButton *donateBtn = ui->centralWidget->findChild<QPushButton*>("donatePushButton");
    if(donateBtn)
        connect(donateBtn, SIGNAL(clicked()), this, SLOT(openPaypalPage()));

    QPushButton *ok = ui->centralWidget->findChild<QPushButton*>("okPushButton");
    QPushButton *cancel = ui->centralWidget->findChild<QPushButton*>("cancelPushButton");

    connect(ok, SIGNAL(clicked()), this, SLOT(savePreferences()));
    connect(ok, SIGNAL(clicked()), this, SLOT(hide()));


    connect(cancel, SIGNAL(clicked()), this, SLOT(hide()));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    // reload project tab's combobox if a new project is added
    projWidget = ui->centralWidget->findChild<ProjectWidget*>("projectWidget");
    connect(prefWidget, SIGNAL(projectAdded()), projWidget, SLOT(fillProjectComboBox()));

    connect(prefWidget, SIGNAL(screenShotEnabled(bool)), this, SLOT(toggleScreenShots(bool)));

    connect(&screenShotTimer, SIGNAL(timeout()), this, SLOT(shotScreen()));

}

void MainWindow::startClock()
{
    isTracking = true;
    trayIcon->setIcon(QIcon(NORMAL_CLOCK_ICON));
    trayIcon->setToolTip(TRACKING_ON);

    trackBeginning = QDateTime::currentDateTime();
}

void MainWindow::stopClock()
{
    createNewTimeSession();

    isTracking = false;
    trayIcon->setIcon(QIcon(OFF_CLOCK_ICON));
    trayIcon->setToolTip(TRACKING_OFF);
}

void MainWindow::toggleTracking()
{    
    if (isTracking) {
        stopClock();        
        screenShotTimer.stop();
    }
    else {
        startClock();
        if (isTakingScreenShots)
            toggleScreenShots(true);
    }
}

void MainWindow::createCommands()
{
    commands = new QMap<QString, TrayIconCommand*>;
    commands->insert(QString("Show main window"),new TrayIconCommand(this, &MainWindow::showNormal));
    commands->insert(QString("Minimize"), new TrayIconCommand(this, &MainWindow::hide));
    commands->insert(QString("Do Nothing"), new TrayIconCommand(this, &MainWindow::doNothing));
    commands->insert(QString("Toggle Tracking"), new TrayIconCommand(this, &MainWindow::toggleTracking));
    preferences->setCommands(commands);
}

void MainWindow::createNewTimeSession()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    TimeSpan gap(trackBeginning, currentTime);
    Project *currentProject = getCurrentProject();
    if (currentProject) {
        currentProject->addTimeTrackingSession(gap);
        // refresh project details widget
        QComboBox *projectCombobox = projWidget->findChild<QComboBox*>("projectComboBox");
        if (projectCombobox &&
            currentProject->getName() == projectCombobox->currentText()){
            projWidget->loadProject();
        }
    }
}

// open a web page with the paypal url asking for a donation using the defaul web browser
void MainWindow::openPaypalPage()
{
    QDesktopServices::openUrl(QUrl(PAYPAL_URL));
}

Project* MainWindow::getCurrentProject()
{
    return Project::getProjectByName(preferences->getCurrentProject());
}

void MainWindow::toggleScreenShots(bool enabled)
{
    isTakingScreenShots = enabled;
    if (isTakingScreenShots && isTracking) {
        QComboBox *screenComboBox = prefWidget->findChild<QComboBox*>("screenComboBox");
        if (screenComboBox) {
            QString text = screenComboBox->currentText();
            int intervalSeconds = 0;
            if (text == "5s") intervalSeconds = 5;
            else if (text == "30s") intervalSeconds = 30;
            else if (text == "1min") intervalSeconds = 60;
            else if (text == "5min") intervalSeconds = 300;
            screenShotTimer.stop();
            screenShotTimer.start(intervalSeconds * 1000);
        }
    }
    else {
        screenShotTimer.stop();
    }
}

// If not exists a folder with the current project name then create one
QString MainWindow::createScreenShotFolder(const QString &projectName)
{
    QDir dir(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) +
             "/" + QApplication::instance()->applicationName() + "/" +
             projectName);
    if (!dir.exists()) {
        qDebug("Dir %s doesn't exists", dir.path().toAscii().data());
        if (!dir.mkdir(dir.path()))
            qDebug("Error: cannot create dir %s", dir.path().toAscii().data());
    }
    return dir.path();
}

void MainWindow::shotScreen()
{
    QString currentProjectName = preferences->getCurrentProject();
    if (currentProjectName.isEmpty())
        return;

    QString path = createScreenShotFolder(currentProjectName) + "/" +
                   QDateTime::currentDateTime().toString("yyyyMMddhhmmss") +
                   ".png";

    ScreenShot::saveNewDesktopScreenshot(path);
}
