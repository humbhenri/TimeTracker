#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>

class Project;
class QStandardItemModel;

namespace Ui {
    class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = 0);
    ~ProjectWidget();

private:
    Ui::ProjectWidget *ui;
    QStandardItemModel* historyModel;
    void prepareHistoryTable();    

public slots:
    void loadProject();
    void fillProjectComboBox();
    void saveProjectDescription();

private slots:
    void on_screenshotsPushButton_clicked();
};

#endif // PROJECTWIDGET_H
