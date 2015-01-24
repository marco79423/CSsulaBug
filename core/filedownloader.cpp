#include "filedownloader.h"
#include "afilesaver.h"
#include "anetworkaccessor.h"

#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

FileDownloader::FileDownloader(QObject *parent, AFileSaver *fileSaver, ANetworkAccessor *networkAccessor) :
    QObject(parent), _fileSaver(fileSaver), _networkAccessor(networkAccessor)
{
    _fileSaver->setParent(this);
    _networkAccessor->setParent(this);

    connect(_networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)), SLOT(_onAccessorReply(const int&, const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finishSignal(const int&)),  SLOT(_onAccessorFinish(const int&)));
}

int FileDownloader::download(const FileDownloader::Task &task, const QString &referer)
{
    /*
      *下載 task 任務
      * task[所要下載的內容] = 所對應的檔案路徑
      */
    const int id = _networkAccessor->get(task.keys(), referer);
    _taskHash[id] = task;
    return  id;
}

void FileDownloader::_onAccessorReply(const int &id, const QString &url, const QByteArray &data)
{
    /*
      *處理 NetworkAccessor 的回應，把內容寫至目標路徑
      */
    QString path = _taskHash[id][url];

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

    emit downloadInfoSignal(id, downloadInfo);
    _taskHash[id].remove(url);
}

void FileDownloader::_onAccessorFinish(const int &id)
{
    /*
      * 當一項任務下載完後，刪除該任務資料
      */

    _taskHash.remove(id);
    emit finishSignal(id);
}

