#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "convertz.h"

class QSortFilterProxyModel;

class AUpdateHandler;
class ADownloadHandler;

class ComicModel;

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString downloadInfo READ getDownloadInfo NOTIFY downloadInfoChanged)

public:

    explicit Core(AUpdateHandler* updateHandler, ADownloadHandler *downloadHandler, QObject *parent = 0);
    QSortFilterProxyModel* getModel() const;
    QString getDownloadInfo() const;

signals:
    
    void updateFinish();
    void downloadFinish();
    void downloadInfoChanged();

public slots:

    void update();
    void download(const QString &key);
    void setFilter(const QString &pattern);
    QString getKey(const int index) const;

    void _onGettingDownloadInfo(const QHash<QString, QString> &info);
private:
    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;
    ADownloadHandler *_downloadHandler;
    ConvertZ _convertz;

    QString _downloadInfo;
};

#endif // CORE_H
