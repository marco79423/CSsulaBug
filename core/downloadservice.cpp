#include "downloadservice.h"
#include "adownloadhandler.h"

#include <QStandardPaths>
#include <QDebug>

DownloadService::DownloadService(ADownloadHandler *downloadHandler, QObject *parent) :
    ADownloadService(parent), _downloadHandler(downloadHandler)
{
    _downloadHandler->setParent(this);

    connect(_downloadHandler, SIGNAL(finish()), SIGNAL(downloadFinish()));
    connect(_downloadHandler, SIGNAL(info(QHash<QString,QString>)), SLOT(_onGettingDownloadProgress(QHash<QString, QString>)));
}


QString DownloadService::getDownloadProgress() const
{
    return _downloadProgress;
}

void DownloadService::download(const QString &key)
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    _downloadHandler->download(key, desktopPath);
}

void DownloadService::_onGettingDownloadProgress(const QHash<QString, QString> &info)
{
    _downloadProgress = QString("[進度 %1%] 下載 %2").arg(info["progress"]).arg(info["path"]);
    qDebug() << "下載進度資訊" << _downloadProgress;
    emit downloadProgressChanged();
}
