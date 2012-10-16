#include "comicmodel.h"
#include "sfupdatehandler.h"
#include "updatehandler.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(QObject *parent) :
    QAbstractListModel(parent)
{
    _updateHandler = new SFUpdateHandler(this);

    QStringList tempRoleNames;
    tempRoleNames << "coverUrl" << "name" << "key"
                  << "site" << "type" << "author"
                  << "lastUpdated";
    for(int i=0; i < tempRoleNames.size(); i++)
        _roleHash[i] = tempRoleNames[i].toUtf8();
    setRoleNames(_roleHash);

    connect(_updateHandler, SIGNAL(info(const QHash<QString,QString>)),
            SLOT(_insertOneEntry(const QHash<QString,QString>)));
    connect(_updateHandler, SIGNAL(finish()), SIGNAL(updateFinish()));
}

int ComicModel::rowCount(const QModelIndex &parent) const
{
    return _comicList.size();
}

QVariant ComicModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _comicList.size())
        return QVariant();

    QHash<QString, QString> comicInfo = _comicList[index.row()];
    return comicInfo[_roleHash[role]];
}


void ComicModel::update()
{
    _updateHandler->update();
}

void ComicModel::_insertOneEntry(const QHash<QString, QString> &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();
}

void ComicModel::d_test()
{
    /*
      * 測試
      */
    update();
}
