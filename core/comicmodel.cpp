#include "comicmodel.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int ComicModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _comicList.size();
}

QVariant ComicModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _comicList.size())
        return QVariant();

    StringHash comicInfo = _comicList[index.row()];
    return comicInfo[roleNames()[role]];
}

QHash<int, QByteArray> ComicModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[CoverUrl] = "coverUrl";
    roleNames[Name] = "name";
    roleNames[Key] = "key";
    roleNames[Site] = "site";
    roleNames[Type] = "type";
    roleNames[Author] = "author";
    roleNames[LastUpdated] = "lastUpdated";
    return roleNames;
}

void ComicModel::insertOneEntry(const StringHash &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();
}

