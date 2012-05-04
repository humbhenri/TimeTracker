#include "projectitemdelegate.h"
#include <QPainter>
#include <QBrush>
#include <QTextItem>

ProjectItemDelegate::ProjectItemDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void ProjectItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
//    int adjust = -5;
//    QRect itemRect = option.rect;
//    itemRect.adjust(adjust, adjust, adjust, adjust);
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(Qt::white);
    }
    else {
        painter->setBrush(QBrush(Qt::black));
    }
    QString projectName = qvariant_cast<QString>(index.data(nameTextRole));
    painter->drawText(option.rect.adjusted(5, 5, 5, 5), projectName);
    painter->restore();
}

QSize ProjectItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 30);
}
