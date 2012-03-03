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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMap>
#include <QDateTime>
#include <QTimer>

class QCloseEvent;
class Preferences;
class PreferencesWidget;
class TrayIconCommand;
class ProjectWidget;
class Project;
class QShortcut;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void setVisible(bool visible);
    virtual void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QAction *toggleAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    Preferences *preferences;
    PreferencesWidget *prefWidget;
    ProjectWidget *projWidget;
    QMap<QString, TrayIconCommand*> *commands;
    bool isTracking;
    bool isTakingScreenShots;
    QDateTime trackBeginning;
    QTimer screenShotTimer;
    QShortcut *nextTabShortcut;
    QShortcut *quitShortcut;
    void createActions();
    void createTrayIcon();
    void fillCheckboxes();
    void makeConnections();
    void createCommands();
    void createNewTimeSession();
    void createNewTimeSession(Project*);
    Project *getCurrentProject();
    QString createScreenShotFolder(const QString &);
    void setUpKeyShortcuts();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void setPreferences();
    inline void doNothing(){}
    void startClock();
    void stopClock();
    void toggleTracking();
    void stopTracking();
    void startTracking();
    void openPaypalPage();
    void toggleScreenShots(bool);
    void shotScreen();
    void updateTrayIconToolTip(QString);
    void switchProject(Project* older);
    void nextTab();
};

#endif // MAINWINDOW_H
