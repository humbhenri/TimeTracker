#include <QStandardItemModel>
#include <QVector>
#include <QMap>

#include "reportwidget.h"
#include "ui_reportwidget.h"
#include "timespan.h"
#include "project.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    prepareReportTableView();
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setDateLabel()));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(fillTableReport()));
    ui->dateEdit->setDate(QDate::currentDate());
}

ReportWidget::~ReportWidget()
{
    delete reportTableModel;
    delete ui;    
}

void ReportWidget::setDateLabel()
{
    ui->dateLabel->setText("<b>" + getDate() + "<\b>");
}

QString ReportWidget::getDate() const
{
    return ui->dateEdit->date().toString();
}

void ReportWidget::fillTableReport()
{
    reportTableModel->removeRows(0, reportTableModel->rowCount());
    QList<QStandardItem*> items;

    QVector<TimeSpan*> timespans = TimeSpan::findAllByDate(ui->dateEdit->date());
    QMap<int, Project*> projects;
    foreach (TimeSpan* timespan, timespans) {
        if (!timespan) continue;
        if (timespan->property("projectId").isValid()) {
            Project *p;
            int projectId = timespan->property("projectId").toInt();
            if (projects.contains(projectId)){
                p = projects.value(projectId);
            }
            else {
                p = Project::getProjectById(projectId);
                projects[projectId] = p;
            }
            if (p) {
                items.append(new QStandardItem(p->getName()));
            }
            items.append(new QStandardItem(timespan->getStart().time().toString()));
            items.append(new QStandardItem(timespan->getEnd().time().toString()));
            items.append(new QStandardItem(timespan->duration()));
            foreach (QStandardItem* item, items)
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            reportTableModel->appendRow(items);
            items.clear();
        }
    }
//    ui->reportTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->reportTableView->model()->sort(0);
    foreach (TimeSpan* timespan, timespans)
        if (timespan) delete timespan;
    foreach (Project* p, projects.values())
        if (p) delete p;
}

void ReportWidget::prepareReportTableView()
{
    reportTableModel = new QStandardItemModel(0, 4, this);
    reportTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Project"));
    reportTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Start"));
    reportTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("End"));
    reportTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Duration"));
    ui->reportTableView->setModel(reportTableModel);
    ui->reportTableView->horizontalHeader()->setStretchLastSection(true);
    ui->reportTableView->setSortingEnabled(true);
}

void ReportWidget::showEvent(QShowEvent *)
{
    fillTableReport();
}
