#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>

class QStandardItemModel;

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

private:
    void prepareReportTableView();
    QStandardItemModel* reportTableModel;
    Ui::ReportWidget *ui;

private slots:
    void setDateLabel();
    void updateReport();
};

#endif // REPORTWIDGET_H
