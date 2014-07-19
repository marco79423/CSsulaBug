#ifndef COMICMODEL_H
#define COMICMODEL_H

#include <QAbstractListModel>

class AUpdateHandler;

class ComicModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit ComicModel(AUpdateHandler *updateHandler, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void d_test();

signals:
    
    void updateFinish();

public slots:

    void update();

private slots:

    void _insertOneEntry(const QHash<QString, QString> &info);

private:

    QList< QHash<QString, QString> > _comicList;
    AUpdateHandler *_updateHandler;
};

#endif // COMICMODEL_H
