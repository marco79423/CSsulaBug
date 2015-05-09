#ifndef COMICINFODELEGATE_H
#define COMICINFODELEGATE_H

#include <QStyledItemDelegate>

class ComicInfoView;

class ComicInfoDelegate : public QStyledItemDelegate
{
public:
    ComicInfoDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    ~ComicInfoDelegate();
private:

    ComicInfoView *_comicInfoView;
};

#endif // COMICINFODELEGATE_H
