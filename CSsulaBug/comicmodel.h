#ifndef COMICMODEL_H
#define COMICMODEL_H

#include <QAbstractListModel>

class UpdateHandler;

class ComicModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit ComicModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:
    
    void updateFinish();

public slots:

    void update();
    
private slots:

    void _insertOneEntry(const QHash<QString, QString> &info);

private:

    QHash<int, QByteArray> _roles;
    QList< QHash<QString, QString> > _comics;

    UpdateHandler *_updateHandler;
};

#endif // COMICMODEL_H
