#ifndef COMICMODEL_H
#define COMICMODEL_H

#include <QAbstractListModel>
#include <QThread>

#include "aupdatehandler.h"

class ComicModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit ComicModel(AUpdateHandler *updateHandler, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    ~ComicModel();

signals:
    
    void updateFinish();

    void _update();

private slots:

    void _insertOneEntry(const StringHash &info);

private:

    QList<StringHash> _comicList;
    AUpdateHandler *_updateHandler;
    QThread _updateThread;
};

#endif // COMICMODEL_H
