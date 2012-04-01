#include "delegate.h"
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QDebug>

Delegate::Delegate(QObject *parent)
    :QItemDelegate(parent)
{
}

void Delegate::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
    //if( option.state & QStyle::State_Selected )
    //    painter->fillRect( option.rect, option.palette.highlight() );
    //qDebug() << index.model()->data(index).toString();
    //painter->drawText(option.rect, index.model()->data(index).toString());
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(600, 100);
}
