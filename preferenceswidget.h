#ifndef PREFERENCESWIDGET_H
#define PREFERENCESWIDGET_H

#include <QWidget>

class Preferences;
class CreateProjectDialog;

namespace Ui {
    class PreferencesWidget;
}

class PreferencesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesWidget(QWidget *parent = 0);
    ~PreferencesWidget();
    void setModel(Preferences*);

private:
    Ui::PreferencesWidget *ui;
    Preferences *preferences;
    CreateProjectDialog *newProjectDialog;

public slots:
    void loadPreferences();
    void loadProjects();
    void addNewProject();
    void showProjectDialog();
    void setCurrentProject(const QString &name);

private slots:
    void on_screenCheckBox_stateChanged(int state);

signals:
    void projectAdded();
    void screenShotEnabled(bool);
};

#endif // PREFERENCESWIDGET_H
