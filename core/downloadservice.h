#ifndef DOWNLOADSERVICE_H
#define DOWNLOADSERVICE_H

#include <QThread>

#include "globals.h"
#include "adownloadservice.h"

class AComicSiteHandler;
class DownloadHandler;

class DownloadService : public ADownloadService
{
    Q_OBJECT

public:

    explicit DownloadService(AComicSiteHandler *comicSiteHandler, QObject *parent = 0);

    QString getDownloadProgress() const;

    ~DownloadService();

signals:

    void _downloadSignal(const QString &key, const QString &dirpath);

public slots:

    void download(const QString &comicKey);
    void download(const QString &comicKey, const StringPair &chapter);

private slots:

     void _onGettingDownloadProgress(const StringHash &info);

private:

    DownloadHandler *_downloadHandler;

    QString _downloadProgress;
    QThread _downloadThread;
};

#endif // DOWNLOADSERVICE_H
