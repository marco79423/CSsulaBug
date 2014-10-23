#include "sortfilterproxycomicmodel.h"
#include "comicmodel.h"

#include <QRegExp>
#include <QTime>
#include <QDebug>

SortFilterProxyComicModel::SortFilterProxyComicModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{
}

void SortFilterProxyComicModel::setComicTypeFilter(const QString &comicTypePattern)
{
    //QTime timer;
    //timer.start();
    _comicTypePattern = comicTypePattern;
    invalidateFilter();
    //qDebug() << timer.elapsed();
}

void SortFilterProxyComicModel::setComicNameFilter(const QString &comicNamePattern)
{
    _comicNamePattern = comicNamePattern;
    invalidateFilter();
}

bool SortFilterProxyComicModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    //篩漫畫類型
    QString comicType = sourceModel()->data(index, ComicModel::Type).toString();
    if(!_comicTypePattern.isEmpty() && !comicType.contains(_comicTypePattern))
    {
        return false;
    }

    //篩漫畫名稱
    QString comicName = sourceModel()->data(index, ComicModel::Name).toString();
    if(!_comicNamePattern.isEmpty() && !comicName.contains(_comicNamePattern))
    {
        return false;
    }

    return true;
}
