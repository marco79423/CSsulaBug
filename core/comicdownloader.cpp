#include "comicdownloader.h"
#include "acomicsitehandler.h"
#include "comicmodel.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

ComicDownloader::ComicDownloader(QObject *parent)
    :QObject(parent),
      _fileDownloader(new FileDownloader(this)),
      _downloadComicModel(new ComicModel(this)),
      _isDownloading(false)
{
    connect(_fileDownloader, SIGNAL(downloadInfoSignal(const QVariantMap&)), SLOT(_onDownloadInfoUpdated(const QVariantMap&)));
    connect(_fileDownloader, SIGNAL(finishSignal()), SLOT(_onTaskFinish()));
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

    if(_downloadComicModel->rowCount() == 1)
    {
        _downloadProcess();
    }
}

void ComicDownloader::abort(const QString &comicKey)
{
    if(_downloadComicModel->getComicInfo(0)["key"].toString() == comicKey)
    {
        _downloadComicModel->removeComicInfo(comicKey);
        _fileDownloader->abort();

        if(_downloadComicModel->rowCount() > 0)
        {
            _downloadProcess();
        }
        else
        {
            emit downloadFinishSignal();
        }
    }
    else
    {
        _downloadComicModel->removeComicInfo(comicKey);
    }
}

void ComicDownloader::_downloadProcess()
{
    QVariantMap comicInfo = _downloadComicModel->getComicInfo(0);
    QVariantMap downloadProgress;
    downloadProgress["message"] = "準備下載 " + comicInfo["name"].toString();
    downloadProgress["ratio"] = 0.0;
    emit downloadProgressChangedSignal(downloadProgress);

    AComicSiteHandler *comicSiteHandler = _comicSiteHandlers[comicInfo["site"].toString()];

    FileDownloader::Task task = _makeTask(comicInfo);
    _fileDownloader->download(task, comicSiteHandler->getReferer());
}

void ComicDownloader::_onDownloadInfoUpdated(const QVariantMap &downloadInfo)
{
    QVariantMap downloadProgress;
    downloadProgress["message"] = "下載 " + downloadInfo["path"].toString();
    downloadProgress["ratio"] = downloadInfo["ratio"];

    emit downloadProgressChangedSignal(downloadProgress);
}

void ComicDownloader::_onTaskFinish()
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

FileDownloader::Task ComicDownloader::_makeTask(const QVariantMap &comicInfo)
{
    FileDownloader::Task task;

    QString dstDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    AComicSiteHandler *comicSiteHandler = _comicSiteHandlers[comicInfo["site"].toString()];
    QList<StringPair> chapters = comicInfo["chapters"].value<QList<StringPair> >();
    foreach(StringPair chapter, chapters)
    {
        QStringList imageUrls = comicSiteHandler->getImageUrls(comicInfo["key"].toString(), chapter.second);

        for(int i=0; i < imageUrls.size(); i++)
        {
            QString imageUrl = imageUrls[i];
            QString filePath = QString("%1/%2/%3/%4.%5").arg(dstDir).arg(comicInfo["name"].toString()).arg(chapter.first).arg(i, 3, 10, QChar('0')).arg(imageUrl.right(3));
            QFileInfo fileInfo(filePath);
            if(fileInfo.exists())
            {
                continue;
            }
            task[imageUrl] = filePath;
        }
    }
    return task;
}

