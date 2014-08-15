#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

#include "globals.h"
#include "convertz.h"

class QSortFilterProxyModel;

class AComicSiteHandler;
class ComicModel;
class FileDownloader;

class Service : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString downloadProgress READ getDownloadProgress NOTIFY downloadProgressChangedSignal)

public:

    explicit Service(AComicSiteHandler *comicSiteHandler, QObject *parent = 0);

    QSortFilterProxyModel* getModel();
    QString getDownloadProgress();

signals:

    void updateFinishedSignal();

    void downloadProgressChangedSignal();
    void downloadFinishSignal();

public slots:

    void update();
    void setFilter(const QString &pattern);
    //virtual StringHash getComicInfo(const int &index) const;

    void download(const int &index);

private slots:

     void _onGettingDownloadProgress(const int &id, const StringHash &info);
     void _onTaskFinish(const int &id, const bool &error);

private:

    AComicSiteHandler *_comicSiteHandler;

    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;

    QString _downloadProgress;
    QList<int> _currentTask;
    FileDownloader *_fileDownloader;

    ConvertZ _convertz;
};

#endif // SERVICE_H
