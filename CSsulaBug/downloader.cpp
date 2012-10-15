#include "downloader.h"
#include "networkaccessor.h"
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
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

    _taskList[id] = task;

    return id;
}

void Downloader::_onAccessorReply(const int &id, QNetworkReply *networkReply)
{
    /*
      *處理 NetworkAccessor 的回應，把內容寫至目標路徑
      */
    QString url = networkReply->url().toString();
    QString path = _taskList[id][url];

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

        _taskList[id].remove(url);
    }

}

void Downloader::_onAccessorFinish(const int &id)
{
    /*
      * 當一項任務下載完後，刪除該任務資料
      */

    emit finish();
    qDebug() << "Downloader:_onAccessorFinish: id " << id << " 下載完成";
    _taskList.remove(id);
}

void Downloader::d_test()
{
    /*
      * 測試
      */

    const QString url1 = "http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe";
    const QString url2 = "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe";

    Task task1;
    task1[url1] = "1a.exe";

    Task task2;
    task2[url1] = "2a.exe";
    task2[url2] = "2b.exe";

    download(task1);
    download(task2);
}
