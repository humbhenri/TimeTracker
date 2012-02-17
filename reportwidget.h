#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>

namespace Ui {
    class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = 0);
    ~ReportWidget();
    QString getDate() const;
    void updateReport();

private:
    Ui::ReportWidget *ui;

private slots:
    void setDateLabel();
};

#endif // REPORTWIDGET_H
