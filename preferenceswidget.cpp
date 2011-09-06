#include "preferenceswidget.h"
#include "ui_preferenceswidget.h"
#include "preferences.h"
#include "trayiconcommand.h"
#include "project.h"
#include "createprojectdialog.h"
#include <QStringList>

PreferencesWidget::PreferencesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreferencesWidget)
{
    ui->setupUi(this);
    newProjectDialog = new CreateProjectDialog;

    ui->screenCheckBox->setChecked(false);

    QStringList screenShotIntervals;
    screenShotIntervals << "5s" << "30s" << "1min" << "5min";
    ui->screenComboBox->addItems(screenShotIntervals);
    ui->screenComboBox->setEnabled(false);

    connect(newProjectDialog, SIGNAL(accepted()), this, SLOT(addNewProject()));
    connect(ui->projectPushButton, SIGNAL(clicked()), this, SLOT(showProjectDialog()));
    connect(ui->projectsComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setCurrentProject(QString)));
}

PreferencesWidget::~PreferencesWidget()
{
    delete ui;
    delete newProjectDialog;
}

void PreferencesWidget::setModel(Preferences *p)
{
    preferences = p;
    connect(p, SIGNAL(changed()), this, SLOT(loadPreferences()));
    loadPreferences();
}

void PreferencesWidget::loadPreferences()
{
    if (preferences) {
        ui->traySingleComboBox->clear();
        ui->trayDoubleComboBox->clear();
        ui->traySingleComboBox->addItems(preferences->commandNames());
        ui->trayDoubleComboBox->addItems(preferences->commandNames());
        QString singleClickCommand = preferences->getSingleClickCommandName();
        QString doubleClickCommand = preferences->getDoubleClickCommandName();
        ui->traySingleComboBox->setCurrentIndex(preferences->commandNames().indexOf(singleClickCommand));
        ui->trayDoubleComboBox->setCurrentIndex(preferences->commandNames().indexOf(doubleClickCommand));        
    }
    loadProjects();
}

void PreferencesWidget::loadProjects()
{
    ui->projectsComboBox->blockSignals(true);
    ui->projectsComboBox->clear();
    QList<Project*> projects = Project::getProjects();
    QList<Project*>::iterator it = projects.begin();
    while (it != projects.end()) {
        ui->projectsComboBox->addItem((*it)->getName());
        it++;
    }
    ui->projectsComboBox->setCurrentIndex(projects.indexOf(Project::getProjectByName(preferences->getCurrentProject())));
    ui->projectsComboBox->blockSignals(false);
}

void PreferencesWidget::addNewProject()
{
    QString name = newProjectDialog->getName();
    QString description = newProjectDialog->getDescription();
    Project *project = Project::makeProject(name, description);
    loadProjects();
    setCurrentProject(project->getName());

    emit projectAdded();
}

void PreferencesWidget::showProjectDialog()
{
    newProjectDialog->clearForms();
    newProjectDialog->exec();
}

void PreferencesWidget::setCurrentProject(const QString &project)
{
#if 0
    qDebug("PreferencesWidget::setCurrentProject called with project = %s", project.toAscii().data());
    QObject* sender = this->sender();
    if (sender)
        qDebug("Sender = %s", sender->objectName().toAscii().data());
#endif
    ui->projectsComboBox->blockSignals(true);
    preferences->setCurrentProject(project);    
    ui->projectsComboBox->setCurrentIndex(Project::getProjects().indexOf(Project::getProjectByName(project)));
    ui->projectsComboBox->blockSignals(false);
}

void PreferencesWidget::on_screenCheckBox_stateChanged(int state)
{
    ui->screenComboBox->setEnabled(state == Qt::Checked);
    emit screenShotEnabled(state == Qt::Checked);
}
