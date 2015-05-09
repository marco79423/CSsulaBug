#include "comicinfodelegate.h"
#include "comicinfoview.h"

#include <QPainter>

ComicInfoDelegate::ComicInfoDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
    _comicInfoView = new ComicInfoView;
}

void ComicInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    _comicInfoView->resize(option.rect.size());
    painter->save();
    painter->translate(option.rect.topLeft());

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, Qt::red);

    _comicInfoView->render(painter);
    painter->restore();
}

ComicInfoDelegate::~ComicInfoDelegate()
{
    delete _comicInfoView;
}

