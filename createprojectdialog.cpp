#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

QString CreateProjectDialog::getName() const
{
    return ui->nameLineEdit->text();
}

QString CreateProjectDialog::getDescription() const
{
    return ui->descriptionTextEdit->document()->toPlainText();
}

void CreateProjectDialog::clearForms()
{
    ui->nameLineEdit->setText("");
    ui->descriptionTextEdit->setText("");
}
