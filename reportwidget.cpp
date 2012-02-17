#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setDateLabel()));
    ui->dateEdit->setDate(QDate::currentDate());
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::setDateLabel()
{
    ui->dateLabel->setText(getDate());
    updateReport();
}

QString ReportWidget::getDate() const
{
    return ui->dateEdit->date().toString();
}

void ReportWidget::updateReport()
{
    //TODO
}
