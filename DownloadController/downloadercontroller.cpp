#include "downloadercontroller.h"
#include "sfdownloadpreparer.h"
#include <QtNetwork>


DownloaderController::DownloaderController(QObject *parent) :
    QObject(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onReply(QNetworkReply*)));

    _downloadPreparer = new SFDownloadPreparer(this);
}

void DownloaderController::download(const QString &key,
                                    const QString &dirPath)
{
    _downloadPreparer->prepare(key);
}

void DownloaderController::onReply(QNetworkReply *reply)
{
}
