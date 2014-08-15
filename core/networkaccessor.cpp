#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

NetworkAccessor::NetworkAccessor(QObject *parent) :
    QObject(parent), _idCount(0), _isAccessing(false)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(_onManagerReply(QNetworkReply*)));
}

int NetworkAccessor::get(const QString &url)
{
    /*
    *   id 為識別值，url 是要下載的網址
    *   get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
    */

    _Task newTask;
    newTask.id = _idCount++;
    newTask.urlList.append(url);

    _taskQueue.enqueue(newTask);
    _startAccess();

    return newTask.id;
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
    _startAccess();

    return newTask.id;
}

QString NetworkAccessor::getHtmlImmediately(const QString &url)
{
    QEventLoop eventLoop;

    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = networkAccessManager->get(_makeRequest(url));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    const QString html = reply->readAll();
    reply->deleteLater();
    networkAccessManager->deleteLater();

    return html;
}

void NetworkAccessor::_startAccess()
{
    /*
      *若是現在沒有實際執行下載任務，便開始執行。
      */
    if(!_isAccessing && !_taskQueue.isEmpty())
    {
        _isAccessing = true;
        _currentTask = _taskQueue.dequeue();

        foreach(QString url, _currentTask.urlList)
        {
            QNetworkRequest request = _makeRequest(url);
            qDebug() << "NetworkAccessor:_startAccess:開始下載 " << url;
            QNetworkReply *reply = _networkAccessManager->get(request);
            _currentTask.replyList.append(reply);
        }
    }
}


void NetworkAccessor::_onManagerReply(QNetworkReply *networkReply)
{
    /*
      * 當 NetWorkAcessManager finish 時，若沒問題，就發送完成任務的訊號，
      * 若是發現還有其他的任務，就會繼續執行
      */

    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerReply: 收到 " << url;

    _currentTask.urlList.removeOne(url);
    _currentTask.replyList.removeOne(networkReply);

    if(networkReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "NetworkAccessor:_onManagerReply:error " << networkReply->error();
        foreach(QNetworkReply *reply, _currentTask.replyList)
        {
            reply->abort();
        }
        _currentTask.urlList.clear();
        _currentTask.replyList.clear();
    }
    else
    {
        emit reply(_currentTask.id, networkReply);
    }

    if(_currentTask.urlList.isEmpty())
    {
        emit finish(_currentTask.id, networkReply->error() != QNetworkReply::NoError);
        _isAccessing = false;
        _startAccess();
    }

    networkReply->deleteLater();
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

