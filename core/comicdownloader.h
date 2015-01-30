#ifndef COMICDOWNLOADER_H
#define COMICDOWNLOADER_H

#include <QObject>
#include <QMap>

#include "globals.h"
#include "filedownloader.h"
#include "convertz.h"

class AComicSiteHandler;
class ComicModel;

class ComicDownloader : public QObject
{
    Q_OBJECT
public:

    explicit ComicDownloader(QObject *parent = 0);
    ComicModel* getDownloadComicModel() const;

signals:

    void downloadProgressChangedSignal(const QVariantMap &downloadProgress);
    void downloadFinishSignal();

public slots:

    void addComicSiteHandler(AComicSiteHandler *comicSiteHandler);
    void download(const QVariantMap &comicInfo);
    void abort(const QString &comicKey);

private slots:

    void _downloadProcess();

    void _onDownloadInfoUpdated(const QVariantMap &downloadInfo);
    void _onTaskFinish();

private:

    QMap<QString, AComicSiteHandler*> _comicSiteHandlers;

    FileDownloader *_fileDownloader;
    ComicModel *_downloadComicModel;

    bool _isDownloading;
    QList<int> _taskIDs;

    FileDownloader::Task _makeTask(const QVariantMap &comicInfo);
};

#endif // COMICDOWNLOADER_H
