#include "sortfilterproxycomicmodel.h"
#include "comicmodel.h"

#include <QRegExp>
#include <QDebug>

SortFilterProxyComicModel::SortFilterProxyComicModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{
}

void SortFilterProxyComicModel::setComicTypeFilter(const QString &comicTypePattern)
{
    _comicTypePattern = comicTypePattern;
    qDebug() << _comicTypePattern;
    invalidateFilter();
}

void SortFilterProxyComicModel::setComicNameFilter(const QString &comicNamePattern)
{
    _comicNamePattern = comicNamePattern;
    invalidateFilter();
    //setFilterRole(ComicModel::Name);
    //setFilterRegExp(QRegExp(comicNamePattern, Qt::CaseInsensitive, QRegExp::FixedString));
}

bool SortFilterProxyComicModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString comicType = sourceModel()->data(index, ComicModel::Type).toString();
    if(!_comicTypePattern.isEmpty() && !comicType.contains(_comicTypePattern))
    {
        return false;
    }

    QString comicName = sourceModel()->data(index, ComicModel::Name).toString();
    if(!_comicNamePattern.isEmpty() && !comicName.contains(_comicNamePattern))
    {
        return false;
    }

    return true;
}
