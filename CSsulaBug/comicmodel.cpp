#include "comicmodel.h"
#include "sfupdatehandler.h"
#include "updatehandler.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QStringList tempRoleNames;
    tempRoleNames << "coverUrl" << "name" << "key"
                  << "site" << "type" << "author"
                  << "lastUpdated";
    for(int i=0; i < tempRoleNames.size(); i++)
        _roles[i] = tempRoleNames[i].toUtf8();
    setRoleNames(_roles);

    _updateHandler = new SFUpdateHandler(this);

    connect(_updateHandler, SIGNAL(info(const QHash<QString,QString>)),
            SLOT(_insertOneEntry(const QHash<QString,QString>)));
    connect(_updateHandler, SIGNAL(finish()), SIGNAL(updateFinish()));
}

int ComicModel::rowCount(const QModelIndex &parent) const
{
    return _comics.size();
}

QVariant ComicModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _comics.size())
        return QVariant();

    QHash<QString, QString> comicInfo = _comics[index.row()];
    return comicInfo[_roles[role]];
}

void ComicModel::update()
{
    _updateHandler->update();
}

void ComicModel::_insertOneEntry(const QHash<QString, QString> &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comics << info;
    endInsertRows();
}
