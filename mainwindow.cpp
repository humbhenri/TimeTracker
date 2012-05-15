/*Copyright 2011 Humberto Pinheiro. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Humberto Pinheiro ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Humberto Pinheiro OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Humberto Pinheiro.*/

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
#include <QShortcut>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "preferences.h"
#include "trayiconcommand.h"
#include "timespan.h"
#include "project.h"
#include "screenshot.h"
#include "clock.h"
#include "projectitemdelegate.h"
#include "projectwidget.h"
#include "createprojectdialog.h"

#define NORMAL_CLOCK_ICON ":/res/images/clock.png"
#define OFF_CLOCK_ICON ":/res/images/clock-off.png"
#define TRACKING_ON "Stop"
#define TRACKING_OFF "Start"
#define WINDOW_ICON NORMAL_CLOCK_ICON
#define PAYPAL_URL "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=VXJX2VJMQKLG2"
#define DBName "timetracker.sqlite"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isTracking(false),
    isTakingScreenShots(false),
    quitShortcut(0),
    trackingClock(new Clock(this)),
    newProjectDialog(new CreateProjectDialog),
    trackBeginning(QDateTime::currentDateTime()),
    preferences(new Preferences)
{
    createTrayIconCommands();
    preferences->loadPreferences();
    setupUI();
    loadProjects();
}

MainWindow::~MainWindow()
{
    stopTracking();
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
    Project *currentProject = getCurrentProject();
    trayIcon->setToolTip(isTracking ? (currentProject ? currentProject->getName() : TRACKING_ON) : TRACKING_OFF);
    trayIcon->show();
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
void MainWindow::setPreferences()
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

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(preferences, SIGNAL(projectChanged(Project*)), this, SLOT(switchProject(Project*)));

    connect(getTrackBtn(), SIGNAL(clicked()), this, SLOT(toggleTracking()));

    connect(trackingClock, SIGNAL(ticked()), this, SLOT(setTimeLabel()));

    QListView * projectLst = ui->centralWidget->findChild<QListView*>("projectLst");
    connect(projectLst, SIGNAL(activated(QModelIndex)), this, SLOT(setSelectedProject(QModelIndex)));
    connect(projectLst, SIGNAL(clicked(QModelIndex)), this, SLOT(setSelectedProject(QModelIndex)));

    QPushButton * btn = ui->centralWidget->findChild<QPushButton*>("newProjectBtn");
    connect(btn, SIGNAL(clicked()), this, SLOT(showProjectDialog()));
    connect(newProjectDialog, SIGNAL(accepted()), this, SLOT(addNewProject()));
}

void MainWindow::startClock()
{
    isTracking = true;
    setTrayIconTrackingMode();
    resetTracking();
}

void MainWindow::stopClock()
{
    createNewTimeSession();
    isTracking = false;
    setTrayIconOffMode();
}

void MainWindow::toggleTracking()
{    
    if (isTracking)
        stopTracking();
    else
        startTracking();
}

void MainWindow::createTrayIconCommands()
{
    commands = new QMap<QString, TrayIconCommand*>;
    commands->insert(QString("Show main window"),new TrayIconCommand(this, &MainWindow::showNormal));
    commands->insert(QString("Minimize"), new TrayIconCommand(this, &MainWindow::hide));
    commands->insert(QString("Do Nothing"), new TrayIconCommand(this, &MainWindow::doNothing));
    commands->insert(QString("Toggle Tracking"), new TrayIconCommand(this, &MainWindow::toggleTracking));
    preferences->setCommands(commands);
    createActions();
}

void MainWindow::createNewTimeSession(Project* p) {
    QDateTime currentTime = QDateTime::currentDateTime();
    TimeSpan * gap = new TimeSpan(trackBeginning, currentTime);
    if (p) {
        p->addTimeTrackingSession(gap);
    }
}

void MainWindow::createNewTimeSession()
{
    createNewTimeSession(getCurrentProject());
}

void MainWindow::openPaypalPage()
{
    QDesktopServices::openUrl(QUrl(PAYPAL_URL));
}

Project* MainWindow::getCurrentProject()
{
    return Project::getProjectByName(preferences->getCurrentProject());
}

void MainWindow::updateTrayIconToolTip(QString txt)
{
    trayIcon->setToolTip(txt);
}

void MainWindow::stopTracking()
{
    if (isTracking) {
        stopClock();
        getTrackBtn()->setText("Start");
        trackingClock->reset();
        trackingClock->stop();
    }
}

void MainWindow::startTracking()
{
    startClock();
    QPushButton *trackBtn = getTrackBtn();
    trackBtn->setText("Stop");
    trackingClock->start();
}

void MainWindow::switchProject(Project *older)
{
    if (isTracking)
        createNewTimeSession(older);
    stopTracking();
}

void MainWindow::setTimeLabel()
{
    QLabel *label = getTimeLabel();
    if (label)
        label->setText(trackingClock->getFormatted());
}

void MainWindow::setSelectedProject(QModelIndex index)
{
    setCursor(Qt::WaitCursor);
    const QAbstractItemModel *model = index.model();
    QString projectName = model->data(index, ProjectItemDelegate::nameTextRole).toString();
    Project *p = Project::getProjectByName(projectName);
    ProjectWidget *widget = ui->centralWidget->findChild<ProjectWidget*>("projectWidget");
    widget->loadProjectDetails(p);
    getTrackBtn()->setEnabled(true);
    preferences->setCurrentProject(projectName);
    setCursor(Qt::ArrowCursor);
}

void MainWindow::showProjectDialog()
{
    newProjectDialog->clearForms();
    newProjectDialog->exec();
}

void MainWindow::setupKeyboardShortcuts()
{
    quitShortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
    connect(quitShortcut, SIGNAL(activated()), qApp, SLOT(quit()));
}

QPushButton * MainWindow::getTrackBtn()
{
    return ui->centralWidget->findChild<QPushButton*>("trackBtn");
}

QLabel *MainWindow::getTimeLabel()
{
    return ui->centralWidget->findChild<QLabel*>("timeLbl");
}

void MainWindow::addNewProject()
{
    QString name = newProjectDialog->getName();
    QString description = newProjectDialog->getDescription();
    Project::makeProject(name, description);
    loadProjects();
}

void MainWindow::prepareProjectListView()
{
    QListView *view = ui->centralWidget->findChild<QListView*>("projectLst");
    QStandardItemModel *model = new QStandardItemModel;
    view->setItemDelegate(new ProjectItemDelegate);
    view->setModel(model);
}


void MainWindow::loadProjects()
{
    QListView *view = ui->centralWidget->findChild<QListView*>("projectLst");
    QStandardItemModel *model = static_cast<QStandardItemModel*>(view->model());
    QVector<Project*> projects = Project::getProjects();
    foreach(Project *p, projects) {
        QStandardItem *item = new QStandardItem();
        item->setData(p->getName(), ProjectItemDelegate::nameTextRole);
        model->appendRow(item);
    }
}

void MainWindow::setupUI()
{
    ui->setupUi(this);
    setWindowIcon(QIcon(WINDOW_ICON));
    createTrayIcon();
    makeConnections();
    setupKeyboardShortcuts();
    prepareProjectListView();
}

void MainWindow::setTrayIconTrackingMode()
{
    trayIcon->setIcon(QIcon(NORMAL_CLOCK_ICON));
    trayIcon->setToolTip(getCurrentProject() ? getCurrentProject()->getName() : TRACKING_ON);
}

void MainWindow::resetTracking()
{
    trackBeginning = QDateTime::currentDateTime();
}

void MainWindow::setTrayIconOffMode()
{
    trayIcon->setIcon(QIcon(OFF_CLOCK_ICON));
    trayIcon->setToolTip(TRACKING_OFF);
}
