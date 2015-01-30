#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

int NetworkAccessor::_idCount = 0;

NetworkAccessor::NetworkAccessor(QObject *parent)
    :ANetworkAccessor(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(_onManagerReply(QNetworkReply*)));
}

int NetworkAccessor::get(const QString &url, const QString &referer)
{
    /*
    *   id 為識別值，url 是要下載的網址
    *   get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
    */
    return get(QStringList() << url, referer);
}

int NetworkAccessor::get(const QStringList &urlList, const QString &referer)
{
    /*
     *id 為識別值，url 是要下載的網址urlList 是要下載的網址清單
     *get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
     */

    _Task newTask;
    newTask.id = _idCount++;
    newTask.urlList = urlList;
    newTask.referer = referer;

    _taskQueue.enqueue(newTask);

    if(_taskQueue.size() == 1)
        _startAccess();

    return newTask.id;
}

void NetworkAccessor::abort(const int &id)
{
    for(int i=0; i < _taskQueue.size(); i++)
    {
        _Task &task = _taskQueue[i];
        if(task.id == id)
        {
            if(i == 0)
            {
                foreach(QNetworkReply *reply, task.replyList)
                {
                    reply->abort();
                }
                _taskQueue.removeAt(i);
                if(!_taskQueue.isEmpty())
                {
                    _startAccess();
                }
            }
            else
            {
                _taskQueue.removeAt(i);
            }

            break;
        }
    }
}

QString NetworkAccessor::getDataImmediately(const QString &url, const QString &referer)
{
    QEventLoop eventLoop;

    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = networkAccessManager->get(_makeRequest(url, referer));
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
    _Task &currentTask = _taskQueue.head();

    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerReply: 收到 " << url;

    if(networkReply->error() == QNetworkReply::OperationCanceledError)
    {
        networkReply->deleteLater();
        return;
    }
    else if(networkReply->error() == QNetworkReply::RemoteHostClosedError)
    {
        qCritical() << networkReply->error() << networkReply->errorString();
        networkReply->deleteLater();
        currentTask.replyList.removeOne(networkReply);

        QNetworkRequest request = _makeRequest(url, currentTask.referer);
        QNetworkReply *newReply = _networkAccessManager->get(request);
        currentTask.replyList.append(newReply);
        return;
    }

    currentTask.urlList.removeOne(url);
    currentTask.replyList.removeOne(networkReply);

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
    _Task &currentTask = _taskQueue.head();
    foreach(QString url, currentTask.urlList)
    {
        QNetworkRequest request = _makeRequest(url, currentTask.referer);
        QNetworkReply *reply = _networkAccessManager->get(request);
        currentTask.replyList.append(reply);
    }
}

QNetworkRequest NetworkAccessor::_makeRequest(const QString &url, const QString &referer)
{
    /*
      *利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request
      */

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36");
    request.setRawHeader("Connection", "close");

    if(!referer.isEmpty())
    {
        request.setRawHeader("Referer", referer.toUtf8());
    }

    return request;
}

