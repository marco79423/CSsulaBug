#ifndef PROXYCOMICMODEL_H
#define PROXYCOMICMODEL_H

#include <QSortFilterProxyModel>

class ProxyComicModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:

    explicit ProxyComicModel(QObject *parent = 0);

public slots:

    void setComicNameFilter(const QString &comicNamePattern);

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:

    QString _comicNamePattern;
};

#endif // PROXYCOMICMODEL_H
