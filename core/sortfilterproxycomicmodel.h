#ifndef SORTFILTERPROXYCOMICMODEL_H
#define SORTFILTERPROXYCOMICMODEL_H

#include <QSortFilterProxyModel>

class SortFilterProxyComicModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:

    explicit SortFilterProxyComicModel(QObject *parent = 0);

public slots:

    void setComicTypeFilter(const QString &comicTypePattern);
    void setComicNameFilter(const QString &comicNamePattern);

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:

    QString _comicTypePattern;
    QString _comicNamePattern;
};

#endif // SORTFILTERPROXYCOMICMODEL_H
