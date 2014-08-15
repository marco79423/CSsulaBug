#include "service.h"
#include "acomicsitehandler.h"
#include "filedownloader.h"
#include "filesaver.h"
#include "comicmodel.h"

#include <QSortFilterProxyModel>
#include <QStandardPaths>
#include <QDebug>

Service::Service(AComicSiteHandler *comicSiteHandler, QObject *parent)
    :QObject(parent), _comicSiteHandler(comicSiteHandler)
{
    _comicSiteHandler->setParent(this);
    _fileDownloader = new FileDownloader(new FileSaver);

    _model = new ComicModel(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);

    connect(_comicSiteHandler, SIGNAL(comicInfoSignal(const StringHash&)), _model,  SLOT(_insertOneEntry(const StringHash&)));
    connect(_comicSiteHandler, SIGNAL(updateFinishedSignal()), this, SIGNAL(updateFinishedSignal()));

    connect(_fileDownloader, SIGNAL(info(const int&, const StringHash&)), SLOT(_onGettingDownloadProgress(const int&, const StringHash&)));
    connect(_fileDownloader, SIGNAL(finish(const int&, const bool&)), SLOT(_onTaskFinish(const int&, const bool&)));
}


QSortFilterProxyModel *Service::getModel()
{
    return _proxyModel;
}

QString Service::getDownloadProgress()
{
    return _downloadProgress;
}

void Service::update()
{
    _comicSiteHandler->updateComicInfos();
}

void Service::setFilter(const QString &pattern)
{
    QString tpattern = _convertz.convertToTraditional(pattern);
    _proxyModel->setFilterRole(1);
    _proxyModel->setFilterRegExp(QRegExp(tpattern, Qt::CaseInsensitive, QRegExp::FixedString));
}
/*
StringHash Service::getComicInfo(const int &index) const
{
    StringHash comicInfo;
    comicInfo["coverUrl"] = _proxyModel->data(_proxyModel->index(index, 0), 0).toString();
    comicInfo["name"] = _proxyModel->data(_proxyModel->index(index, 0), 1).toString();
    comicInfo["key"] = _proxyModel->data(_proxyModel->index(index, 0), 2).toString();
    comicInfo["site"] = _proxyModel->data(_proxyModel->index(index, 0), 3).toString();
    comicInfo["type"] = _proxyModel->data(_proxyModel->index(index, 0), 4).toString();
    comicInfo["author"] = _proxyModel->data(_proxyModel->index(index, 0), 5).toString();
    comicInfo["lastUpdated"] = _proxyModel->data(_proxyModel->index(index, 0), 6).toString();

    return comicInfo;
}*/

void Service::download(const int &index)
{
    QString dstDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString name = _proxyModel->data(_proxyModel->index(index, 0), 1).toString();
    QString comicKey = _proxyModel->data(_proxyModel->index(index, 0), 2).toString();

    QList<StringPair> chapters = _comicSiteHandler->getChapters(comicKey);
    foreach(StringPair chapter, chapters)
    {
        QStringList imageUrls = _comicSiteHandler->getImageUrls(comicKey, chapter.second);

        FileDownloader::Task task;
        for(int i=0; i < imageUrls.size(); i++)
        {
            QString imageUrl = imageUrls[i];
            QString filePath = QString("%1/%2/%3/%4.%5").arg(dstDir).arg(name).arg(chapter.first).arg(i, 3, 10, QChar('0')).arg(imageUrl.right(3));
            task[imageUrl] = filePath;
        }

        const int id = _fileDownloader->download(task);
        _currentTask.append(id);
    }
}

void Service::_onGettingDownloadProgress(const int &id, const StringHash &info)
{
    _downloadProgress = QString("[進度 %1%] 下載 %2").arg(info["progress"]).arg(info["path"]);
    qDebug() << "下載進度資訊" << _downloadProgress;
    emit downloadProgressChangedSignal();
}

void Service::_onTaskFinish(const int &id, const bool &error)
{
    _currentTask.removeAll(id);
    if(_currentTask.isEmpty())
    {
        emit downloadFinishSignal();
    }
}
