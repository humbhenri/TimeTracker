#include "projectitemdelegate.h"
#include "project.h"
#include <QPainter>
#include <QBrush>

ProjectItemDelegate::ProjectItemDelegate(Project *p, QObject *parent) :
    project(p),
    QAbstractItemDelegate(parent)
{
}

void ProjectItemDelegate::setProject(Project *p)
{
    project = p;
}

Project *ProjectItemDelegate::getProject() const
{
    return project;
}

void ProjectItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setBrush(option.palette.highlightedText());
    }
    else {
        painter->setBrush(QBrush(Qt::black));
        if (index.row() % 2 == 0)
            painter->fillRect(option.rect, option.palette.dark());
        else
            painter->fillRect(option.rect, option.palette.light());
    }
    painter->drawText(10, 10, project->getName());
}

QSize ProjectItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 50);
}
