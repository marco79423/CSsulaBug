#include "comicdownloader.h"
#include "acomicsitehandler.h"
#include "filesaver.h"
#include "comicmodel.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

ComicDownloader::ComicDownloader(QObject *parent)
    :QObject(parent),
      _fileDownloader(new FileDownloader(new FileSaver, this)),
      _downloadComicModel(new ComicModel(this)),
      _isDownloading(false)
{
    connect(_fileDownloader, SIGNAL(downloadInfoSignal(const int&, const QVariantMap&)), SLOT(_onDownloadInfoUpdated(const int&, const QVariantMap&)));
    connect(_fileDownloader, SIGNAL(finishSignal(const int&)), SLOT(_onTaskFinish(const int&)));
}

ComicModel *ComicDownloader::getDownloadComicModel() const
{
    return _downloadComicModel;
}


void ComicDownloader::addComicSiteHandler(AComicSiteHandler *comicSiteHandler)
{
    _comicSiteHandlers[comicSiteHandler->getComicSiteName()] = comicSiteHandler;
}

void ComicDownloader::download(const QVariantMap &comicInfo)
{
    _downloadComicModel->insertComicInfo(comicInfo);

    if(!_isDownloading)
    {
        _isDownloading = true;
        _downloadProcess();
    }
}

void ComicDownloader::_downloadProcess()
{
    if(!_isDownloading)
    {
        return;
    }

    QVariantMap comicInfo = _downloadComicModel->getComicInfo(0);
    QVariantMap downloadProgress;
    downloadProgress["message"] = "準備下載 " + comicInfo["name"].toString();
    downloadProgress["ratio"] = 0.0;
    emit downloadProgressChangedSignal(downloadProgress);

    AComicSiteHandler *comicSiteHandler = _comicSiteHandlers[comicInfo["site"].toString()];

    QList<FileDownloader::Task> tasks = _makeTasks(comicInfo);
    foreach(FileDownloader::Task task, tasks)
    {
        const int id = _fileDownloader->download(task, comicSiteHandler->getReferer());
        _taskIDs.append(id);
    }
}

void ComicDownloader::_onDownloadInfoUpdated(const int &id, const QVariantMap &downloadInfo)
{
    Q_UNUSED(id)

    QVariantMap downloadProgress;
    downloadProgress["message"] = "下載 " + downloadInfo["path"].toString();

    int total = _downloadComicModel->getComicInfo(0)["chapters"].value<QList<StringPair> >().size();
    downloadProgress["ratio"] = float(total - _taskIDs.size()) / total;

    emit downloadProgressChangedSignal(downloadProgress);
}

void ComicDownloader::_onTaskFinish(const int &id)
{
    _taskIDs.removeAll(id);
    if(_taskIDs.isEmpty())
    {
        _downloadComicModel->removeComicInfo(0);
        if(_downloadComicModel->rowCount() > 0)
        {
            _downloadProcess();
        }
        else
        {
            emit downloadFinishSignal();
        }
    }
}

QList<FileDownloader::Task> ComicDownloader::_makeTasks(const QVariantMap &comicInfo)
{
    QList<FileDownloader::Task> tasks;

    QString dstDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    AComicSiteHandler *comicSiteHandler = _comicSiteHandlers[comicInfo["site"].toString()];
    QList<StringPair> chapters = comicInfo["chapters"].value<QList<StringPair> >();
    foreach(StringPair chapter, chapters)
    {
        QFileInfo fileInfo(QString("%1/%2/%3").arg(dstDir).arg(comicInfo["name"].toString()).arg(chapter.first));
        if(fileInfo.exists())
        {
            continue;
        }

        QStringList imageUrls = comicSiteHandler->getImageUrls(comicInfo["key"].toString(), chapter.second);

        FileDownloader::Task task;
        for(int i=0; i < imageUrls.size(); i++)
        {
            QString imageUrl = imageUrls[i];
            QString filePath = QString("%1/%2/%3/%4.%5").arg(dstDir).arg(comicInfo["name"].toString()).arg(chapter.first).arg(i, 3, 10, QChar('0')).arg(imageUrl.right(3));
            task[imageUrl] = filePath;
        }
        tasks.append(task);
    }
    return tasks;
}

