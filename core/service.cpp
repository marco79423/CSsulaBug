#include "service.h"
#include "acomicsitehandler.h"
#include "filedownloader.h"
#include "filesaver.h"
#include "comicmodel.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>


Service::Service(AComicSiteHandler *comicSiteHandler, QObject *parent)
    :AService(parent), _comicSiteHandler(comicSiteHandler)
{
    _comicSiteHandler->setParent(this);
    _fileDownloader = new FileDownloader(new FileSaver);

    _model = new ComicModel(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);

    connect(_comicSiteHandler, SIGNAL(comicInfoSignal(const StringHash&)), _model,  SLOT(insertOneEntry(const StringHash&)));
    connect(_comicSiteHandler, SIGNAL(updateFinishedSignal()), this, SLOT(_onUpdateFinished()));

    connect(_fileDownloader, SIGNAL(info(const int&, const StringHash&)), SLOT(_onGettingDownloadProgress(const int&, const StringHash&)));
    connect(_fileDownloader, SIGNAL(finish(const int&, const bool&)), SLOT(_onTaskFinish(const int&, const bool&)));
}


QSortFilterProxyModel *Service::getModel()
{
    return _proxyModel;
}

QStringList Service::getChapterNames(const QString &comicKey)
{
    if(!_chapterInfo.contains(comicKey))
    {
        _chapterInfo[comicKey] = _comicSiteHandler->getChapters(comicKey);
    }
    QStringList chapterNames;
    foreach(StringPair chapter, _chapterInfo[comicKey])
    {
        chapterNames.append(chapter.first);
    }
    return chapterNames;
}

void Service::update()
{
    setProperty("isUpdatingStatus", true);

    _comicSiteHandler->updateComicInfos();
}

void Service::setFilter(const QString &pattern)
{
    QString tpattern = _convertz.convertToTraditional(pattern);
    _proxyModel->setFilterRole(1);
    _proxyModel->setFilterRegExp(QRegExp(tpattern, Qt::CaseInsensitive, QRegExp::FixedString));
}

void Service::download(const QString &comicKey)
{
    download(comicKey, getChapterNames(comicKey));
}

void Service::download(const QString &comicKey, const QStringList &chapterNames)
{
    setProperty("isDownloadingStatus", true);

    QString dstDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QModelIndex modelIndex = _proxyModel->match(_proxyModel->index(0, 0), 2, comicKey)[0];
    QString name = _proxyModel->data(modelIndex, 1).toString();

    setProperty("downloadProgress", QString("準備下載 ...").arg(name));

    QList<StringPair> chapters = _chapterInfo[comicKey];
    foreach(StringPair chapter, chapters)
    {
        QFileInfo fileInfo(QString("%1/%2/%3").arg(dstDir).arg(name).arg(chapter.first));
        if(!chapterNames.contains(chapter.first) || fileInfo.exists())
        {
            continue;
        }

        QStringList imageUrls = _comicSiteHandler->getImageUrls(comicKey, chapter.second);

        FileDownloader::Task task;
        for(int i=0; i < imageUrls.size(); i++)
        {
            QString imageUrl = imageUrls[i];
            QString filePath = QString("%1/%2/%3/%4.%5").arg(dstDir).arg(name).arg(chapter.first).arg(i, 3, 10, QChar('0')).arg(imageUrl.right(3));
            task[imageUrl] = filePath;
        }

        const int id = _fileDownloader->download(task);
        _currentTaskIDs.append(id);
    }

    _currentTaskSize = _currentTaskIDs.size();

    if(_currentTaskIDs.isEmpty())
    {
        qDebug() << "下載結束";
        setProperty("isDownloadingStatus", false);
        emit downloadFinishSignal();
    }
}

void Service::_onUpdateFinished()
{
    qDebug() << "更新結束";
    setProperty("isUpdatingStatus", false);
    emit updateFinishedSignal();
}

void Service::_onGettingDownloadProgress(const int &id, const StringHash &info)
{
    Q_UNUSED(id)

    setProperty("downloadProgress", QString("[進度 %2/%3 ] 下載 %4").arg(_currentTaskSize - _currentTaskIDs.size()).arg(_currentTaskSize).arg(info["path"]));
    qDebug() << "下載進度資訊" << property("downloadProgress").toString();
}

void Service::_onTaskFinish(const int &id, const bool &error)
{
    Q_UNUSED(error)

    _currentTaskIDs.removeAll(id);
    if(_currentTaskIDs.isEmpty())
    {
        qDebug() << "下載結束";
        setProperty("isDownloadingStatus", false);
        emit downloadFinishSignal();
    }
}
