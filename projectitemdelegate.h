#ifndef PROJECTITEMDELEGATE_H
#define PROJECTITEMDELEGATE_H

#include <QAbstractItemDelegate>

class ProjectItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    ProjectItemDelegate(QObject *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    enum datarole {nameTextRole = Qt::UserRole + 100};
private:
};

#endif // PROJECTITEMDELEGATE_H
