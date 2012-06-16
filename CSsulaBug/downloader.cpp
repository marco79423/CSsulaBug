#include "downloader.h"
#include "networkaccessor.h"
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

Downloader::Downloader(QObject *parent) :
    QObject(parent), _taskIdCount(0)
{
    _networkAccessor = new NetworkAccessor(this);

    _setConnection();
}

void Downloader::download(const Downloader::Task &task)
{
    /*
      *下載 task 任務
      * task.urlList 所要下載的內容
      * task.pathList[url] 所對應的檔案路徑
      */
    _networkAccessor->get(++_taskIdCount, task.urlList);
    qDebug() << "Downloader:download: 下載任務 " << _taskIdCount;

    _pathList[_taskIdCount] = task.pathList;
}

void Downloader::_onAccessorReply(const int &id, QNetworkReply *networkReply)
{
    /*
      *處理 NetworkAccessor 的回應，把內容寫至目標路徑
      */
    QString url = networkReply->url().toString();
    QString path = _pathList[id][url];

    QFileInfo fileInfo(path);
    if(!fileInfo.exists())
    {
        QDir dir = fileInfo.absoluteDir();
        if(!dir.exists() && !dir.mkpath(dir.absolutePath()))
        {
            qCritical() << "Downloader:_onAccessorReply:資料夾"
                        << dir.absolutePath()
                        << "建立失敗";
        }

        QFile file(path);
        if(!file.open(QFile::WriteOnly))
        {
            qCritical() << "Downloader:_onAccessorReply: 開啟 " << path << " 失敗";
            return;
        }

        file.write(networkReply->readAll());
        file.close();

        QHash<QString, QString> downloadInfo;
        downloadInfo["url"] = url;
        downloadInfo["path"] = path;
        emit info(downloadInfo);
        qDebug() << "Downloader:_onAccessorReply: 已下載 " << path;

        _pathList[id].remove(url);
    }

}

void Downloader::_onAccessorFinish(const int &id)
{
    /*
      * 當一項任務下載完後，刪除該任務資料
      */

    emit finish();
    qDebug() << "Downloader:_onAccessorFinish: id " << id << " 下載完成";
    _pathList.remove(id);
}

void Downloader::_setConnection()
{
    /*
      *設定連結
      */

    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&)),
            SLOT(_onAccessorFinish(const int&)));
}
