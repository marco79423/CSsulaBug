#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

int NetworkAccessor::_idCount = 0;

NetworkAccessor::NetworkAccessor(QObject *parent)
    :QObject(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(_onManagerReply(QNetworkReply*)));
}

int NetworkAccessor::get(const QString &url)
{
    /*
    *   id 為識別值，url 是要下載的網址
    *   get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
    */
    return get(QStringList() << url);
}

int NetworkAccessor::get(const QStringList &urlList)
{
    /*
     *id 為識別值，url 是要下載的網址urlList 是要下載的網址清單
     *get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
     */

    _Task newTask;
    newTask.id = _idCount++;
    newTask.urlList = urlList;

    _taskQueue.enqueue(newTask);

    if(_taskQueue.size() == 1)
        _startAccess();

    return newTask.id;
}

QString NetworkAccessor::getDataImmediately(const QString &url)
{
    QEventLoop eventLoop;

    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = networkAccessManager->get(_makeRequest(url));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    eventLoop.exec();

    reply->deleteLater();
    networkAccessManager->deleteLater();

    return reply->readAll();
}

void NetworkAccessor::_onManagerReply(QNetworkReply *networkReply)
{
    /*
      * 當 NetWorkAcessManager finish 時，若沒問題，就發送完成任務的訊號，
      * 若是發現還有其他的任務，就會繼續執行
      */

    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerReply: 收到 " << url;

    if(networkReply->error() == QNetworkReply::RemoteHostClosedError)
    {
        qCritical() << networkReply->error() << networkReply->errorString();
        networkReply->deleteLater();

        QNetworkRequest request = _makeRequest(url);
        _networkAccessManager->get(request);
        return;
    }

    _Task &currentTask = _taskQueue.head();
    currentTask.urlList.removeOne(url);

    emit replySignal(currentTask.id, url, networkReply->readAll());
    networkReply->deleteLater();

    if(currentTask.urlList.isEmpty())
    {
        emit finishSignal(currentTask.id);
        _taskQueue.dequeue();

        if(!_taskQueue.isEmpty())
        {
            _startAccess();
        }
    }
}

void NetworkAccessor::_startAccess()
{
    foreach(QString url, _taskQueue.head().urlList)
    {
        QNetworkRequest request = _makeRequest(url);
        _networkAccessManager->get(request);
    }
}

QNetworkRequest NetworkAccessor::_makeRequest(const QString &url)
{
    /*
      *利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request
      */

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36");
    request.setRawHeader("Connection", "close");

    return request;
}

