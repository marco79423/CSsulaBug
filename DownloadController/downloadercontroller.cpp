#include "downloadercontroller.h"
#include <QtNetwork>

DownloaderController::DownloaderController(QObject *parent) :
    QObject(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(done(QNetworkReply*)));
}

void DownloaderController::download(const QString &url,
                                    const QString &dirPath)
{
    _networkAccessManager->get(QNetworkRequest(url));
}

void DownloaderController::done(QNetworkReply *reply)
{

}
