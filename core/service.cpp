#include "service.h"
#include "acomicsitehandler.h"
#include "filedownloader.h"
#include "filesaver.h"
#include "comicmodel.h"
#include "sortfilterproxycomicmodel.h"
#include "comicdownloader.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>


Service::Service(QObject *parent)
    :AService(parent)
{
    _model = new ComicModel(this);
    _proxyModel = new SortFilterProxyComicModel(this);
    _proxyModel->setSourceModel(_model);

    _comicDownloader = new ComicDownloader(this);
    connect(_comicDownloader, SIGNAL(downloadProgressChangedSignal(const QVariantMap&)), SLOT(_onDownloadProgressChanged(const QVariantMap&)));
    connect(_comicDownloader, SIGNAL(downloadFinishSignal()), SLOT(_onDownloadFinished()));
}

void Service::addComicSiteHandler(AComicSiteHandler *comicSiteHandler)
{
    comicSiteHandler->setParent(this);
    connect(comicSiteHandler, SIGNAL(comicInfoSignal(const QVariantMap&)), _model,  SLOT(insertComicInfo(const QVariantMap&)));
    connect(comicSiteHandler, SIGNAL(updateFinishedSignal()), this, SLOT(_onUpdateFinished()));

    _comicSiteHandlers[comicSiteHandler->getComicSiteName()] = comicSiteHandler;

    _comicDownloader->addComicSiteHandler(comicSiteHandler);
}


SortFilterProxyComicModel *Service::getModel()
{
    return _proxyModel;
}

QStringList Service::getChapterNames(const QString &comicKey)
{
    QVariantMap comicInfo = _model->getComicInfo(comicKey);

    if(!comicInfo.contains("chapters"))
    {
        QString site = comicInfo["site"].toString();
        comicInfo["chapters"].setValue(_comicSiteHandlers[site]->getChapters(comicKey));
        _model->setComicInfo(comicInfo);
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

void Service::update()
{
    setProperty("isUpdatingStatus", true);

    foreach(AComicSiteHandler* comicSiteHandler, _comicSiteHandlers)
    {
        comicSiteHandler->update();
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
    setProperty("isDownloadingStatus", true);

    QVariantMap comicInfo = _model->getComicInfo(comicKey);

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

void Service::_onUpdateFinished()
{
    static int updateFinishedCounter = 0;
    if(++updateFinishedCounter == _comicSiteHandlers.size())
    {
        updateFinishedCounter = 0;

        qDebug() << "更新結束";
        setProperty("isUpdatingStatus", false);
        emit updateFinishedSignal();
    }
}

void Service::_onDownloadProgressChanged(const QVariantMap &downloadProgress)
{
    setProperty("downloadProgress", downloadProgress);
}

void Service::_onDownloadFinished()
{
    qDebug() << "下載結束";
    setProperty("isDownloadingStatus", false);
    emit downloadFinishSignal();
}
