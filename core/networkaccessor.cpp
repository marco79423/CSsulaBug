#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

NetworkAccessor::NetworkAccessor(QObject *parent)
    :ANetworkAccessor(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(_onManagerReply(QNetworkReply*)));
}

bool NetworkAccessor::isBusy() const
{
    return !_replyList.isEmpty();
}

bool NetworkAccessor::get(const QString &url, const QString &referer)
{
    if(isBusy())
    {
        return false;
    }
    return get(QStringList() << url, referer);
}

bool NetworkAccessor::get(const QStringList &urlList, const QString &referer)
{
    if(isBusy())
    {
        return false;
    }

    _referer = referer;

    foreach(QString url, urlList)
    {
        QNetworkRequest request = _makeRequest(url, _referer);
        QNetworkReply *reply = _networkAccessManager->get(request);
        _replyList.append(reply);
    }
    return true;
}

void NetworkAccessor::abort()
{
    foreach(QNetworkReply *reply, _replyList)
    {
        reply->abort();
    }
}

QByteArray NetworkAccessor::getDataImmediately(const QString &url, const QString &referer)
{
    QEventLoop eventLoop;
    QNetworkAccessManager networkAccessManager(this);

    QNetworkReply *reply = networkAccessManager.get(_makeRequest(url, referer));
    connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    eventLoop.exec();
    reply->deleteLater();

    return reply->readAll();
}

void NetworkAccessor::_onManagerReply(QNetworkReply *networkReply)
{
    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerReply: 收到 " << url;

    _replyList.removeOne(networkReply);
    emit replySignal(networkReply);

    if(_replyList.isEmpty())
    {
        emit finishSignal();
    }
}


QNetworkRequest NetworkAccessor::_makeRequest(const QString &url, const QString &referer)
{
    /*
      *利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request
      */

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36");
    //request.setRawHeader("Connection", "close");

    if(!referer.isEmpty())
    {
        request.setRawHeader("Referer", referer.toUtf8());
    }

    return request;
}

