#ifndef PROJECTITEMDELEGATE_H
#define PROJECTITEMDELEGATE_H

#include <QAbstractItemDelegate>

class Project;

class ProjectItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    ProjectItemDelegate(Project *p = 0, QObject *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setProject(Project *p);
    Project *getProject() const;
private:
    Project *project;
};

#endif // PROJECTITEMDELEGATE_H
