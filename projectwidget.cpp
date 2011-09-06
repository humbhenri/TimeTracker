#include "projectwidget.h"
#include "ui_projectwidget.h"
#include "project.h"
#include "timespan.h"
#include "project.h"
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

ProjectWidget::ProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    prepareHistoryTable();
    fillProjectComboBox();

    connect(ui->projectComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(loadProject()));
    connect(ui->descriptionTextEdit, SIGNAL(textChanged()), this, SLOT(saveProjectDescription()));
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::prepareHistoryTable()
{
    historyModel = new QStandardItemModel(0, 2, this);
    historyModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Beginning"));
    historyModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Duration"));
    ui->historyTableView->setModel(historyModel);
    ui->historyTableView->horizontalHeader()->setStretchLastSection(true);
    ui->historyTableView->setColumnWidth(0, 130);
}

void ProjectWidget::loadProject()
{
    Project *project = Project::getProjectByName(ui->projectComboBox->currentText());
    if (!project)
        return;

    ui->descriptionTextEdit->setText( project->getDescription());
    ui->timeSpentLabel->setText(project->totalTimeSpent());

    QList<TimeSpan> timeSpans = project->getTimeSpans();
    QList<TimeSpan>::iterator it = timeSpans.begin();
    historyModel->removeRows(0, historyModel->rowCount());
    QList<QStandardItem*> items;
    while (it != timeSpans.end()) {
        QStandardItem *beginning = new QStandardItem((*it).beginning().toString("MMM dd yyyy hh:mm:ss"));
        QStandardItem *duration = new QStandardItem((*it).toString());
        items.append(beginning);
        items.append(duration);
        historyModel->appendRow(items);
        items.clear();
        it++;
    }
    ui->historyTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void ProjectWidget::fillProjectComboBox()
{
    ui->projectComboBox->blockSignals(true);
    ui->projectComboBox->clear();
    QList<Project*> projects = Project::getProjects();
    QList<Project*>::iterator it = projects.begin();
    while (it != projects.end()) {
        ui->projectComboBox->addItem((*it)->getName());
        it++;
    }
    ui->projectComboBox->blockSignals(false);
    loadProject();
}

void ProjectWidget::saveProjectDescription()
{
    Project *project = Project::getProjectByName(ui->projectComboBox->currentText());
    if (!project)
        return;
    project->setDescription(ui->descriptionTextEdit->document()->toPlainText());

#if 0
    qDebug("ProjectWidget::saveProjectDescription %s", project->getDescription().toAscii().data());
#endif
}

void ProjectWidget::on_screenshotsPushButton_clicked()
{
    QString projectName = ui->projectComboBox->currentText();
    QString path = QDir(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) +
             "/" + QApplication::instance()->applicationName() + "/" +
             projectName).path();
    qDebug(path.toAscii().data());
    QDesktopServices::openUrl(QUrl("file:///" + path));
}
