#ifndef CORE_H
#define CORE_H

#include <QObject>

class QSortFilterProxyModel;

class ComicModel;
class DownloadHandler;

class Core : public QObject
{
    Q_OBJECT

public:

    explicit Core(QObject *parent = 0);
    QSortFilterProxyModel* model() const;

signals:
    
    void updateFinish();

public slots:

    void update();
    void download(const QString &key, const QString &dstDir);
    void setFilter(const QString &pattern);
    QString getKey(const int index) const;

private:

    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;
    DownloadHandler *_downloadHandler;
};

#endif // CORE_H
