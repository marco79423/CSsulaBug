#include "sortfilterproxycomicmodel.h"
#include "comicmodel.h"

#include <QRegExp>
#include <QTime>
#include <QDebug>

SortFilterProxyComicModel::SortFilterProxyComicModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{
}

void SortFilterProxyComicModel::setComicNameFilter(const QString &comicNamePattern)
{
    _comicNamePattern = comicNamePattern;
    invalidateFilter();
}

bool SortFilterProxyComicModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    //篩漫畫名稱
    QString comicName = sourceModel()->data(index, ComicModel::Name).toString();
    if(!_comicNamePattern.isEmpty() && !comicName.contains(_comicNamePattern))
    {
        return false;
    }

    return true;
}
