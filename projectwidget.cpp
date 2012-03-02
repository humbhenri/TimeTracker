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

    connect(ui->projectComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(loadProjectDetails()));
//    connect(ui->descriptionTextEdit, SIGNAL(textChanged()), this, SLOT(saveProjectDescription()));
    ui->descriptionTextEdit->installEventFilter(this);
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

void ProjectWidget::loadProjectDetails()
{
    Project *project = Project::getProjectByName(ui->projectComboBox->currentText());
    if (!project)
        return;

    ui->descriptionTextEdit->setText( project->getDescription());
    ui->timeSpentLabel->setText(project->totalTimeSpent());

    QVector<TimeSpan*> timeSpans = project->getTimeSpans();
    QVector<TimeSpan*>::iterator it = timeSpans.begin();
    historyModel->removeRows(0, historyModel->rowCount());
    QList<QStandardItem*> items;
    while (it != timeSpans.end()) {
        QStandardItem *beginning = new QStandardItem((*it)->getStart().toString("MMM dd yyyy hh:mm:ss"));
        beginning->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        QStandardItem *duration = new QStandardItem((*it)->toString());
        duration->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
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
    QStringList projects = Project::getProjects();
    QStringList::iterator it = projects.begin();
    while (it != projects.end()) {
        ui->projectComboBox->addItem(*it);
        it++;
    }
    ui->projectComboBox->blockSignals(false);
    loadProjectDetails();
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

bool ProjectWidget::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->descriptionTextEdit && event->type() == QEvent::FocusOut) {
        saveProjectDescription();
        return true;
    }
    return false;
}
