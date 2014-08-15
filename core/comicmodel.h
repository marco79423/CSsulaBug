#ifndef COMICMODEL_H
#define COMICMODEL_H

#include <QAbstractListModel>

#include "globals.h"

class ComicModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit ComicModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:

    void _insertOneEntry(const StringHash &info);

private:

    QList<StringHash> _comicList;
};

#endif // COMICMODEL_H
