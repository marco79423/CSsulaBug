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
    roleNames[0] = "coverUrl";
    roleNames[1] = "name";
    roleNames[2] = "key";
    roleNames[3] = "site";
    roleNames[4] = "type";
    roleNames[5] = "author";
    roleNames[6] = "lastUpdated";
    return roleNames;
}

void ComicModel::insertOneEntry(const StringHash &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();
}

