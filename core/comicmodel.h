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
        UpdateStatus,
        Chapters
    };

    explicit ComicModel(QObject *parent = 0);
    
    QVariantMap getComicInfo(const QString &comicKey);
    QVariantMap getComicInfo(const int &row);
    Q_INVOKABLE bool hasComicInfo(const QString &comicKey);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

signals:

    void comicInfoInsertedSignal(const QString &comicKey);
    void comicInfoRemovedSignal(const QString &comicKey);

public slots:

    void insertComicInfo(const QVariantMap &info);
    void removeComicInfo(const QString &comicKey);
    void updateComicInfo(const QVariantMap &comicInfo);

private:

    QList<QVariantMap> _comicList;
};

#endif // COMICMODEL_H
