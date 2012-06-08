#include "sfcoverupdater.h"
#include "networkaccessor.h"

#include <QStringList>
#include <QDebug>

SFCoverUpdater::SFCoverUpdater(QObject *parent) :
    QObject(parent), _state(Prepared)
{
    _networkAccessor = new NetworkAccessor(this);
    connect(_networkAccessor,
            SIGNAL(oneReply(const QString&, const QByteArray&)),
            SLOT(onOneReply(const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finish()), SLOT(onReplyFinish()));
}

SFCoverUpdater::State SFCoverUpdater::getState() const
{
    return _state;
}

QList<ComicInfo> SFCoverUpdater::getComicList() const
{
    return _comicInfoList;
}

int SFCoverUpdater::getCoverCounts() const
{
    return _coverCount;
}

void SFCoverUpdater::update(const QList<ComicInfo> &comicInfoList)
{
    qDebug() << "SFCoverUpdater::update start ...";
    if(_state != Prepared) qCritical() << "SFCoverUpdater::isn't prepared";

    initialize();

    qDebug() << "SFCoverUpdater::change state to CoverImageGetting";
    _state = CoverImageGetting;

    _comicInfoList = comicInfoList;
    QStringList coverUrlList;
    for(int i=0; i < _comicInfoList.count(); i++)
    {
        if(!_comicInfoList[i].hasCover())
        {
            QString url = _comicInfoList[i].getCoverUrl();
            _coverMap[url] = i;
            coverUrlList.append(url);
            qDebug() << "SFCoverUpdater:: prepare url " << url;
        }
    }

    if(!coverUrlList.isEmpty())
       ;// _networkAccessor->get(coverUrlList);
}



void SFCoverUpdater::onOneReply(const QString &url, const QByteArray &content)
{
    qDebug() << "SFCoverUpdater::onOneReply start ...";

    if(_state == CoverImageGetting)
    {
        processCoverImageData(url, content);
    }
}

void SFCoverUpdater::onReplyFinish()
{
    qDebug() << "SFUpdater::onReplyFinish start ...";
    if(_state == CoverImageGetting)
    {
        _state = Prepared;
        qDebug() << "SFCoverUpdater:::finish, coverCount = " << _coverCount;
        emit finish();
    }
}

void SFCoverUpdater::initialize()
{
    _coverCount = 0;
    _comicInfoList.clear();
}

void SFCoverUpdater::processCoverImageData(const QString &url,
                                           const QByteArray &content)
{
    qDebug() << "SFCoverUpdater::processCoverImage start ...";
    QImage cover;
    if(!cover.loadFromData(content))
    {
        qDebug() << "SFUpdater::cover loading failed";
    }

    ComicInfo info = _comicInfoList[_coverMap[url]];
    info.setCover(cover);
    _comicInfoList[_coverMap[url]] = info;
    emit comicInfo(info);

    qDebug() << "SFUpdater::coverCount:" << ++_coverCount;
}
