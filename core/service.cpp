#include "service.h"
#include "acomicsitehandler.h"
#include "filedownloader.h"
#include "comicmodel.h"
#include "sortfilterproxycomicmodel.h"
#include "comicdownloader.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>


Service::Service(QObject *parent)
    :AService(parent)
{
    _comicModel = new ComicModel(this);
    _proxyModel = new SortFilterProxyComicModel(this);
    _proxyModel->setSourceModel(_comicModel);

    _comicDownloader = new ComicDownloader(this);
    connect(_comicDownloader, SIGNAL(downloadProgressChangedSignal(const QVariantMap&)), SLOT(_onDownloadProgressChanged(const QVariantMap&)));
    connect(_comicDownloader, SIGNAL(downloadFinishSignal()), SLOT(_onDownloadFinished()));
}

void Service::addComicSiteHandler(AComicSiteHandler *comicSiteHandler)
{
    comicSiteHandler->setParent(this);
    connect(comicSiteHandler, SIGNAL(comicInfoSignal(const QVariantMap&)), _comicModel,  SLOT(insertComicInfo(const QVariantMap&)));
    connect(comicSiteHandler, SIGNAL(collectingFinishedSignal()), this, SLOT(_onCollectingFinished()));

    _comicSiteHandlers[comicSiteHandler->getComicSiteName()] = comicSiteHandler;

    _comicDownloader->addComicSiteHandler(comicSiteHandler);
}


SortFilterProxyComicModel *Service::getComicModel()
{
    return _proxyModel;
}

QStringList Service::getChapterNames(const QString &comicKey)
{
    QVariantMap comicInfo = _comicModel->getComicInfo(comicKey);

    if(!comicInfo.contains("chapters"))
    {
        QString site = comicInfo["site"].toString();
        comicInfo["chapters"].setValue(_comicSiteHandlers[site]->getChapters(comicKey));
        _comicModel->updateComicInfo(comicInfo);
    }
    QStringList chapterNames;
    foreach(StringPair chapter, comicInfo["chapters"].value<QList<StringPair> >())
    {
        chapterNames.append(chapter.first);
    }
    return chapterNames;
}

ComicModel *Service::getDownloadComicModel()
{
    return _comicDownloader->getDownloadComicModel();
}

void Service::collectComicInfos()
{
    setProperty("collectingStatus", true);

    foreach(AComicSiteHandler* comicSiteHandler, _comicSiteHandlers)
    {
        comicSiteHandler->collectComicInfos();
    }
}

void Service::setComicNameFilter(const QString &comicNamePattern)
{
    _proxyModel->setComicNameFilter(_convertz.convertToTraditional(comicNamePattern));
}

void Service::download(const QString &comicKey)
{
    download(comicKey, getChapterNames(comicKey));
}

void Service::download(const QString &comicKey, const QStringList &chapterNames)
{
    setProperty("downloadStatus", true);

    QVariantMap comicInfo = _comicModel->getComicInfo(comicKey);

    QList<StringPair> results;

    QList<StringPair> chapters = comicInfo["chapters"].value<QList<StringPair> >();
    foreach(StringPair chapter, chapters)
    {
        if(chapterNames.contains(chapter.first))
        {
            results.append(chapter);
        }
    }
    comicInfo["chapters"].setValue(results);
    _comicDownloader->download(comicInfo);
}

void Service::abort(const QString &comicKey)
{
    _comicDownloader->abort(comicKey);
}

void Service::_onCollectingFinished()
{
    static int collectingFinishedCounter = 0;
    if(++collectingFinishedCounter == _comicSiteHandlers.size())
    {
        collectingFinishedCounter = 0;

        qDebug() << "更新結束";
        setProperty("collectingStatus", false);
        emit collectingFinishedSignal();
    }
}

void Service::_onDownloadProgressChanged(const QVariantMap &downloadProgress)
{
    setProperty("downloadProgress", downloadProgress);
    emit downloadProgressChangedSignal();
}

void Service::_onDownloadFinished()
{
    qDebug() << "下載結束";
    setProperty("downloadStatus", false);
    emit downloadFinishedSignal();
}
