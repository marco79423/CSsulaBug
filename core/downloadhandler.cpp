#include "downloadhandler.h"

#include "acomicsitehandler.h"
#include "filedownloader.h"
#include "filesaver.h"

DownloadHandler::DownloadHandler(AComicSiteHandler *comicSiteHandler, QObject *parent)
    :QObject(parent), _comicSiteHandler(comicSiteHandler), _fileDownloader(new FileDownloader(new FileSaver, this))
{
    _comicSiteHandler->setParent(this);

    connect(_fileDownloader, SIGNAL(info(const StringHash&)), SIGNAL(downloadInfoSignal(const StringHash&)));
    connect(_fileDownloader, SIGNAL(finish()), SIGNAL(downloadFinishedSignal()));
}

void DownloadHandler::download(const QString &comicKey, const QString &dstDir)
{
    QList<StringPair> chapters = _comicSiteHandler->getChapters(comicKey);
    foreach(StringPair chapter, chapters)
    {
        download(comicKey, chapter, dstDir);
    }
}

void DownloadHandler::download(const QString &comicKey, const StringPair &chapter, const QString &dstDir)
{
    QStringList imageUrls = _comicSiteHandler->getImageUrls(comicKey, chapter.second);

    FileDownloader::Task task;
    for(int i=0; i < imageUrls.size(); i++)
    {
        QString imageUrl = imageUrls[i];
        QString filePath = QString("%1/%2.%3").arg(dstDir).arg(chapter.first).arg(i, 3, 10, QChar('0')).arg(imageUrl.right(3));
        task[imageUrl] = filePath;
    }

    _fileDownloader->download(task);
}
