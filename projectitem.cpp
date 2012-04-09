#include "projectitem.h"
#include "ui_projectitem.h"

ProjectItem::ProjectItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectitem)
{
    ui->setupUi(this);
}

ProjectItem::~ProjectItem()
{
    delete ui;
}
