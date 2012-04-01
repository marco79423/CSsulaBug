#include "htmldownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>
#include <QFile>
#include <QImageReader>
#include <QBuffer>

HtmlDownloader::HtmlDownloader(QObject *parent) :
    QObject(parent)
{
    _networkManager = new QNetworkAccessManager(this);
    connect(_networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(done(QNetworkReply*)));
}

void HtmlDownloader::request(const QString &url)
{
    QNetworkRequest request(url);
    _networkManager->get(request);
}

void HtmlDownloader::done(QNetworkReply *reply)
{
    if(reply->error())
    {
        qCritical() << "HtmlDownloader::done: error " << reply->error();
        return;
    }
    //QBuffer buffer(reply->readAll());
    QImageReader reader(reply, "PNG");
    QImage image = reader.read();
    image.save("test2.png");

    reply->deleteLater();
}

