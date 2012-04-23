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
    ui(new Ui::ProjectWidget),
    selectedProject(0)
{
    ui->setupUi(this);    

    prepareHistoryTable();
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::prepareHistoryTable()
{
    historyModel = new QStandardItemModel(0, 3, this);
    historyModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Start"));
    historyModel->setHeaderData(1, Qt::Horizontal, QObject::tr("End"));
    historyModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Duration"));
    ui->historyTableView->setModel(historyModel);
    ui->historyTableView->horizontalHeader()->setStretchLastSection(true);
    ui->historyTableView->setColumnWidth(0, 130);
    ui->historyTableView->setAlternatingRowColors(true);
}

void ProjectWidget::loadProjectDetails(Project *project)
{
    selectedProject = project;

    if (!project)
        return;

    ui->timeSpentLabel->setText(project->totalTimeSpent());

    historyModel->removeRows(0, historyModel->rowCount());

    QVector<TimeSpan*> timeSpans = project->getTimeSpans();
    QVectorIterator<TimeSpan*> it(timeSpans);
    it.toBack();
    QList<QStandardItem*> items;
    while (it.hasPrevious()) {
        TimeSpan *ts = it.previous();
        QStandardItem *beginning = new QStandardItem(ts->getStart().toString("MMM dd yyyy hh:mm:ss"));
        beginning->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        QStandardItem *end = new QStandardItem(ts->getEnd().toString("MMM dd yyyy hh:mm:ss"));
        end->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        QStandardItem *duration = new QStandardItem(ts->duration());
        duration->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        items.append(beginning);
        items.append(end);
        items.append(duration);
        historyModel->appendRow(items);
        items.clear();        
    }
    ui->historyTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void ProjectWidget::on_screenshotsPushButton_clicked()
{
    if (!selectedProject)
        return;
    QString projectName = selectedProject->getName();
    QString path = QDir(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) +
             "/" + QApplication::instance()->applicationName() + "/" +
             projectName).path();
    qDebug(path.toAscii().data());
    QDesktopServices::openUrl(QUrl("file:///" + path));
}
