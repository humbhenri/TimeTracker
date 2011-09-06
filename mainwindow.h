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
    void createActions();
    void createTrayIcon();
    void fillCheckboxes();
    void makeConnections();
    void createCommands();
    void createNewTimeSession();    
    Project *getCurrentProject();
    QString createScreenShotFolder(const QString &);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void savePreferences();
    inline void doNothing(){}
    void startClock();
    void stopClock();
    void toggleTracking();
    void openPaypalPage();
    void toggleScreenShots(bool);
    void shotScreen();
};

#endif // MAINWINDOW_H
