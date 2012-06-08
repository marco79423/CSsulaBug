#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

NetworkAccessor::NetworkAccessor(QObject *parent) :
    QObject(parent), _isAccessing(false)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    _setConnection();
}

void NetworkAccessor::get(const int &id, const QString &url)
{
    /*
    *   id 為識別值，url 是要下載的網址
    *   get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
    */

    Task newTask;
    newTask.id = id;

    newTask.urlList.append(url);
    qDebug() << "NetworkAccessor:get:準備下載 " << url;

    _taskQueue.enqueue(newTask);
    _startAccess();
}

void NetworkAccessor::get(const int &id, const QStringList &urlList)
{
    /*
     *id 為識別值，url 是要下載的網址urlList 是要下載的網址清單
     *get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
     */

    Task newTask;
    newTask.id = id;
    foreach(QString url, urlList)
    {
        newTask.urlList.append(url);
        qDebug() << "NetworkAccessor:get:準備下載 " << url;
    }
    _taskQueue.enqueue(newTask);
    _startAccess();
}


void NetworkAccessor::_setConnection()
{
    /*
      *設定連結
      */

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onManagerFinish(QNetworkReply*)));
}

void NetworkAccessor::_startAccess()
{
    /*
      *若是現在沒有實際執行下載任務，便開始執行。
      */

    if(!_isAccessing && !_taskQueue.isEmpty())
    {
        _isAccessing = true;
        foreach(QString url, _taskQueue.head().urlList)
        {
            QNetworkRequest request = _makeRequest(url);
            _networkAccessManager->get(request);
            qDebug() << "NetworkAccessor:_startAccess:開始下載 " << url;
        }
    }
}

void NetworkAccessor::onManagerFinish(QNetworkReply *networkReply)
{
    /*
      *當 NetWorkAcessManager finish 時，
      *刪除 _taskQueue 的此項，並負責發送加上 id 的 reply signal
      *若是發現該任務已經結束了，便發送 finish
      */

    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerFinish: 收到 " << url;

    if(networkReply->error())
    {
        qCritical() << "NetworkAccessor:onManagerFinish:error " << url;
        networkReply->deleteLater();
        return;
    }

     _taskQueue.head().urlList.removeOne(url);
    emit reply(_taskQueue.head().id, networkReply);
    networkReply->deleteLater();

    if(_taskQueue.head().urlList.isEmpty())
    {
        emit finish(_taskQueue.head().id);
        if(!_taskQueue.isEmpty())
            _taskQueue.dequeue();
        _isAccessing = false;
        _startAccess();
    }
}

QNetworkRequest NetworkAccessor::_makeRequest(const QString &url)
{
    /*
      *利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request
      */

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");
    return request;
}

