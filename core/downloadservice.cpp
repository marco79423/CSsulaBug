#include "downloadservice.h"
#include "downloadhandler.h"

#include <QStandardPaths>
#include <QDebug>

DownloadService::DownloadService(AComicSiteHandler *comicSiteHandler, QObject *parent) :
    ADownloadService(parent)
{
    _downloadHandler = new DownloadHandler(comicSiteHandler);

    connect(this, SIGNAL(_downloadSignal(const QString&, const QString&)), _downloadHandler, SLOT(download(const QString&, const QString&)));
    connect(_downloadHandler, SIGNAL(downloadInfoSignal(const StringHash&)), SLOT(_onGettingDownloadProgress(const StringHash&)));
    connect(_downloadHandler, SIGNAL(downloadFinishedSignal()), SIGNAL(downloadFinish()));
    connect(&_downloadThread, SIGNAL(finished()), _downloadHandler, SLOT(deleteLater()));

    _downloadHandler->moveToThread(&_downloadThread);
    _downloadThread.start();
}


QString DownloadService::getDownloadProgress() const
{
    return _downloadProgress;
}

DownloadService::~DownloadService()
{
    _downloadThread.quit();
    _downloadThread.wait();
}


void DownloadService::download(const QString &comicKey)
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    emit _downloadSignal(comicKey, desktopPath);
}

void DownloadService::download(const QString &comicKey, const StringPair &chapter)
{

}

void DownloadService::_onGettingDownloadProgress(const StringHash &info)
{
    _downloadProgress = QString("[進度 %1%] 下載 %2").arg(info["progress"]).arg(info["path"]);
    qDebug() << "下載進度資訊" << _downloadProgress;
    emit downloadProgressChanged();
}
