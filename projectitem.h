#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QWidget>

namespace Ui {
    class projectitem;
}

class ProjectItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectItem(QWidget *parent = 0);
    ~ProjectItem();

private:
    Ui::projectitem *ui;
};

#endif // PROJECTITEM_H
