#include "filedownloader.h"
#include "afilesaver.h"
#include "anetworkaccessor.h"

#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

FileDownloader::FileDownloader(QObject *parent, AFileSaver *fileSaver, ANetworkAccessor *networkAccessor) :
    QObject(parent), _taskSize(0), _fileSaver(fileSaver), _networkAccessor(networkAccessor)
{
    _fileSaver->setParent(this);
    _networkAccessor->setParent(this);

    connect(_networkAccessor, SIGNAL(replySignal(QNetworkReply*)), SLOT(_onAccessorReply(QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finishSignal()),  SLOT(_onAccessorFinish()));
}

bool FileDownloader::download(const FileDownloader::Task &task, const QString &referer)
{
    if(_networkAccessor->isBusy())
    {
        return false;
    }
    _currentTask = task;
    _taskSize = task.size();
    return _networkAccessor->get(_currentTask.keys(), referer);
}

void FileDownloader::abort()
{
    return _networkAccessor->abort();
}

void FileDownloader::_onAccessorReply(QNetworkReply* reply)
{
    QString url = reply->url().toString();
    QString path = _currentTask[url];

    _currentTask.remove(url);

    if(reply->error() != QNetworkReply::NoError)
    {
        if(!QNetworkReply::OperationCanceledError)
        {
            qCritical() << reply->errorString();
        }
    }
    else
    {
        _fileSaver->saveFile(reply->readAll(), path);

        QVariantMap downloadInfo;
        downloadInfo["url"] = url;
        downloadInfo["path"] = path;
        downloadInfo["ratio"] = float(_taskSize - _currentTask.size()) / _taskSize;
        emit downloadInfoSignal(downloadInfo);
    }

    reply->deleteLater();
}

void FileDownloader::_onAccessorFinish()
{
    emit finishSignal();
}

