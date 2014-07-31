#include "downloader.h"
#include "networkaccessor.h"
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

Downloader::Downloader(AFileSaver *fileSaver, QObject *parent) :
    QObject(parent), _fileSaver(fileSaver)
{
    _fileSaver->setParent(this);

    _networkAccessor = new NetworkAccessor(this);

    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&)),
            SLOT(_onAccessorFinish(const int&)));
}

int Downloader::download(const Downloader::Task &task)
{
    /*
      *下載 task 任務
      * task[所要下載的內容] = 所對應的檔案路徑
      */
    int id = _networkAccessor->get(task.keys());
    qDebug() << "Downloader:download: 下載任務 " << id;

    _taskHash[id] = task;

    return id;
}

void Downloader::_onAccessorReply(const int &id, QNetworkReply *networkReply)
{
    /*
      *處理 NetworkAccessor 的回應，把內容寫至目標路徑
      */
    QString url = networkReply->url().toString();
    QString path = _taskHash[id][url];

    QHash<QString, QString> downloadInfo;
    downloadInfo["url"] = url;
    downloadInfo["path"] = path;

    AFileSaver::SaverStatus saverStatus = _fileSaver->saveFile(networkReply->readAll(), path);
    switch(saverStatus)
    {
        case AFileSaver::SaverStatus::FileExists:
            qCritical() << "Downloader:_onAccessorReply:目標檔案存在";
            break;
        case AFileSaver::SaverStatus::FailedToCreateDstDir:
            qCritical() << "Downloader:_onAccessorReply:目標資料夾建立失敗";
            break;
        case AFileSaver::SaverStatus::FailedToCreateDstFile:
            qCritical() << "Downloader:_onAccessorReply: 目標檔案開啟失敗";
            break;
        case AFileSaver::SaverStatus::FailedToWriteDstFile:
            qCritical() << "Downloader:_onAccessorReply: 目標檔案寫入失敗";
            break;
        default:
            break;
    }

    qDebug() << "Downloader:_onAccessorReply: 已下載 " << path;
    emit info(downloadInfo);
    _taskHash[id].remove(url);
}

void Downloader::_onAccessorFinish(const int &id)
{
    /*
      * 當一項任務下載完後，刪除該任務資料
      */

    _taskHash.remove(id);

    qDebug() << "Downloader:_onAccessorFinish: id " << id << " 下載完成";
    emit finish();
}

