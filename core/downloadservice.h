#ifndef DOWNLOADSERVICE_H
#define DOWNLOADSERVICE_H

#include <QThread>

#include "adownloadservice.h"
#include "adownloadhandler.h"

class DownloadService : public ADownloadService
{
    Q_OBJECT

public:

    explicit DownloadService(ADownloadHandler *downloadHandler, QObject *parent = 0);

    QString getDownloadProgress() const;

    ~DownloadService();

signals:

    void _downloadSignal(const QString &key, const QString &dirpath);

public slots:

    void download(const QString &key);

private slots:

     void _onGettingDownloadProgress(const StringHash &info);

private:

    ADownloadHandler *_downloadHandler;

    QString _downloadProgress;
    QThread _downloadThread;
};

#endif // DOWNLOADSERVICE_H
