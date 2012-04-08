#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

NetworkAccessor::NetworkAccessor(QObject *parent) :
    QObject(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onReply(QNetworkReply*)));
}

void NetworkAccessor::get(const QString &url)
{
    qDebug() << "NetworkAccessor::start get...";
    _checkList.clear();

    _checkList.append(url);

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");

    _networkAccessManager->get(request);
    qDebug() << "NetworkAccessor::send request " << request.url();
}

void NetworkAccessor::get(const QList<QString> &urlList)
{
    qDebug() << "NetworkAccessor::start get...";

    _checkList = urlList;

    QNetworkRequest request;
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");

    foreach(QString url, urlList)
    {
        qDebug() << "url "<<url;
        request.setUrl(QUrl(url));

        _networkAccessManager->get(request);

        qDebug() << "NetworkAccessor::send request " << request.url();
    }

}

void NetworkAccessor::onReply(QNetworkReply *reply)
{
    qDebug() << "NetworkAccessor::get one reply";
    if(reply->error())
    {
        qCritical() << tr("NetworkAccessor:: error") << reply->error();
        reply->deleteLater();
        return;
    }

    const QString url = reply->url().toString();
    const QString content = reply->readAll();


    emit oneReply(url, content);
    emit oneReply(content);
    qDebug() << "NetworkAccessor::send a signal for " << url;

    _checkList.removeOne(url);

    if(_checkList.empty())
    {
        emit finish();
        qDebug() << "NetworkAccessor::finish";
    }

    reply->deleteLater();
}

