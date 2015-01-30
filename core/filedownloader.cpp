#include "filedownloader.h"
#include "afilesaver.h"
#include "anetworkaccessor.h"

#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

FileDownloader::FileDownloader(QObject *parent, AFileSaver *fileSaver, ANetworkAccessor *networkAccessor) :
    QObject(parent), _counter(0), _downloading(false), _fileSaver(fileSaver), _networkAccessor(networkAccessor)
{
    _fileSaver->setParent(this);
    _networkAccessor->setParent(this);

    connect(_networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)), SLOT(_onAccessorReply(const int&, const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finishSignal(const int&)),  SLOT(_onAccessorFinish(const int&)));
}

int FileDownloader::download(const FileDownloader::Task &task, const QString &referer)
{
    if(_downloading)
        return -1;

    _downloading = true;
    _currentTask = task;
    _taskId = _networkAccessor->get(_currentTask.keys(), referer);
    return _taskId;
}

void FileDownloader::abort()
{
    if(_downloading)
    {
        _networkAccessor->abort(_taskId);
        _downloading = false;
        _counter = 0;
    }
}

void FileDownloader::_onAccessorReply(const int &id, const QString &url, const QByteArray &data)
{
    /*
      *處理 NetworkAccessor 的回應，把內容寫至目標路徑
      */
    QString path = _currentTask[url];

    QVariantMap downloadInfo;
    downloadInfo["url"] = url;
    downloadInfo["path"] = path;

    AFileSaver::SaverStatus saverStatus = _fileSaver->saveFile(data, path);
    switch(saverStatus)
    {
        case AFileSaver::FileExists:
            qCritical() << "FileDownloader:_onAccessorReply:目標檔案存在";
            break;
        case AFileSaver::FailedToCreateDstDir:
            qCritical() << "FileDownloader:_onAccessorReply:目標資料夾建立失敗";
            break;
        case AFileSaver::FailedToCreateDstFile:
            qCritical() << "FileDownloader:_onAccessorReply: 目標檔案開啟失敗";
            break;
        case AFileSaver::FailedToWriteDstFile:
            qCritical() << "FileDownloader:_onAccessorReply: 目標檔案寫入失敗";
            break;
        default:
            break;
    }


    _counter += 1;
    downloadInfo["ratio"] = float(_counter) / _currentTask.size();
    emit downloadInfoSignal(downloadInfo);
}

void FileDownloader::_onAccessorFinish(const int &id)
{
    Q_UNUSED(id)
    _downloading = false;
    _counter = 0;
    emit finishSignal();
}

