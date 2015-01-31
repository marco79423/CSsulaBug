#include "filedownloader.h"
#include "anetworkaccessor.h"

#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

FileDownloader::FileDownloader(QObject *parent, ANetworkAccessor *networkAccessor) :
    QObject(parent), _taskSize(0), _networkAccessor(networkAccessor)
{
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
        _saveFile(reply->readAll(), path);

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

bool FileDownloader::_saveFile(const QByteArray &data, const QString &filePath)
{
    //檢查目標檔案是否存在
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists())
    {
        return false;
    }

    //檢查對應的資料夾是否存在，若不存在則建立
    QDir dir = fileInfo.absoluteDir();
    if(!dir.exists() && !dir.mkpath(dir.absolutePath()))
    {
        return false;
    }

    //檢查是可以開啟目標檔案
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }

    //寫入檔案
    if(file.write(data) == -1)
    {
        return false;
    }
    file.close();

    return true;
}

