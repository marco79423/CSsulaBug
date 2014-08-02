#ifndef DOWNLOADSERVICE_H
#define DOWNLOADSERVICE_H

#include "adownloadservice.h"

class ADownloadHandler;

class DownloadService : public ADownloadService
{
    Q_OBJECT

public:

    explicit DownloadService(ADownloadHandler *downloadHandler, QObject *parent = 0);

    QString getDownloadProgress() const;

public slots:

    void download(const QString &key);

private slots:

     void _onGettingDownloadProgress(const QHash<QString, QString> &info);

private:

    ADownloadHandler *_downloadHandler;

    QString _downloadProgress;
};

#endif // DOWNLOADSERVICE_H
