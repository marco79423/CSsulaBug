#include "comicdownloader.h"
#include "comicsitehandler/acomicsitehandler.h"
#include "comicmodel.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

ComicDownloader::ComicDownloader(QObject *parent)
    :QObject(parent),
      _downloading(false),
      _fileDownloader(new FileDownloader(this)),
      _downloadComicModel(new ComicModel(this))
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
    _downloadProcess();
}

void ComicDownloader::abort(const QString &comicKey)
{
    if(_downloadComicModel->getComicInfo(0)["key"].toString() == comicKey)
    {
        _fileDownloader->abort();
    }
    else
    {
        _downloadComicModel->removeComicInfo(comicKey);
    }
}

void ComicDownloader::_downloadProcess()
{
    if(_downloadComicModel->rowCount() == 0)
    {
        emit downloadFinishSignal();
        return;
    }

    if(_downloading)
    {
        return;
    }
    _downloading = true;

    QVariantMap comicInfo = _downloadComicModel->getComicInfo(0);

    _updateDownloadProgress(0.0, "準備下載 " + comicInfo["name"].toString());

    AComicSiteHandler *comicSiteHandler = _comicSiteHandlers[comicInfo["site"].toString()];

    FileDownloader::Task task = _makeTask(comicInfo, comicSiteHandler);
    if(task.isEmpty())
    {
        _updateDownloadProgress(0.0, comicInfo["name"].toString() + " 不需要下載");
        _onTaskFinish();
        return;
    }
    _fileDownloader->download(task, comicSiteHandler->getReferer());
}

void ComicDownloader::_onDownloadInfoUpdated(const QVariantMap &downloadInfo)
{
    _updateDownloadProgress(
        downloadInfo["ratio"].toFloat(), "下載 " + downloadInfo["path"].toString()
    );
}


void ComicDownloader::_onTaskFinish()
{
    _downloading = false;
    _downloadComicModel->removeComicInfo(0);
    _downloadProcess();
}

FileDownloader::Task ComicDownloader::_makeTask(const QVariantMap &comicInfo, AComicSiteHandler* comicSiteHandler)
{
    FileDownloader::Task task;

    QString dstDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

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

void ComicDownloader::_updateDownloadProgress(const float &radio, const QString &message)
{
    QVariantMap downloadProgress;
    downloadProgress["ratio"] = radio;
    downloadProgress["message"] = message;

    emit downloadProgressChangedSignal(downloadProgress);
}

