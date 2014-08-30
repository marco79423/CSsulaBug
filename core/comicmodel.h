#ifndef COMICMODEL_H
#define COMICMODEL_H

#include <QAbstractListModel>

#include "globals.h"

class ComicModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum RoleName
    {
        CoverUrl,
        Name,
        Key,
        Site,
        Type,
        Author,
        LastUpdated
    };

    explicit ComicModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:

    void insertComicInfo(const StringHash &info);

private:

    QList<StringHash> _comicList;
};

#endif // COMICMODEL_H
