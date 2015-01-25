#include "comicmodel.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariantMap ComicModel::getComicInfo(const QString &comicKey)
{
    foreach(QVariantMap comicInfo, _comicList)
    {
        if(comicInfo["key"] == comicKey)
        {
            return comicInfo;
        }
    }
    return QVariantMap();
}

QVariantMap ComicModel::getComicInfo(const int &row)
{
    return _comicList[row];
}

bool ComicModel::hasComicInfo(const QString &comicKey)
{
    foreach(QVariantMap comicInfo, _comicList)
    {
        if(comicInfo["key"] == comicKey)
        {
            return true;
        }
    }
    return false;
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

    QVariantMap comicInfo = _comicList[index.row()];
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
    roleNames[UpdateStatus] = "updateStatus";
    roleNames[Chapters] = "chapters";
    return roleNames;
}

void ComicModel::insertComicInfo(const QVariantMap &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();

    emit comicInfoInsertedSignal(info["key"].toString());
}

void ComicModel::removeComicInfo(const QString &comicKey)
{
    int index = 0;
    for(; index < _comicList.size(); index++)
    {
        if(_comicList[index]["key"] == comicKey)
        {
            break;
        }
    }

    beginRemoveRows(QModelIndex(), index, index);
    _comicList.removeAt(index);
    endRemoveRows();

    emit comicInfoRemovedSignal(comicKey);
}

void ComicModel::updateComicInfo(const QVariantMap &comicInfo)
{
    for(int i=0; i< _comicList.size(); i++)
    {
        if(_comicList[i]["key"] == comicInfo["key"])
        {
            _comicList[i] = comicInfo;
            break;
        }
    }
}

