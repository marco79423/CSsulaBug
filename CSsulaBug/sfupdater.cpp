#include "sfupdater.h"
#include "networkaccessor.h"
#include <QRegExp>
#include <QDebug>

SFUpdater::SFUpdater(QObject *parent) :
    QObject(parent), _state(Prepared), _comicCount(0), _coverCount(0)
{
    _networkAccessor = new NetworkAccessor(this);
    connect(_networkAccessor,
            SIGNAL(oneReply(const QString&, const QByteArray&)),
            SLOT(onOneReply(const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finish()), SLOT(onReplyFinish()));
}

SFUpdater::State SFUpdater::getState() const
{
    return _state;
}

QList<ComicInfo> SFUpdater::getComicList() const
{
    return _comicInfoList;
}

int SFUpdater::getComicCounts() const
{
    if(_state != Prepared) qCritical() << "SFUpdater::isn't prepared";
    return _comicCount;
}

int SFUpdater::getCoverCounts() const
{
    if(_state != Prepared) qCritical() << "SFUpdater::isn't prepared";
    return _coverCount;
}

void SFUpdater::update()
{
    qDebug() << "SFUpdate::update start ...";
    if(_state != Prepared) qCritical() << "SFUpdater::isn't prepared";

    initialize();

    qDebug() << "SFUpdate::change state to PageNumberGetting";
    _state = PageNumberGetting;

    qDebug() << "SFUpdate::get http://comic.sfacg.com/Catalog/";
    _networkAccessor->get("http://comic.sfacg.com/Catalog/");
}

void SFUpdater::onOneReply(const QString& url,const QByteArray &content)
{
    qDebug() << "SFUpdate::onOneReply start ...";

    if(_state == PageNumberGetting)
    {
        qDebug() << "SFUpdate::change state to KeyNameListing";

        const int maxPageNumber = getMaxPageNumber(content);
        const QStringList pagePageUrlList = getPageUrlList(maxPageNumber);

        _state = ComicDataGetting;
        _networkAccessor->get(pagePageUrlList);
    }
    else if(_state == ComicDataGetting)
    {
        processComicData(content);
    }
    else if(_state == CoverImageGetting)
    {
        processCoverImage(url, content);
    }
}

void SFUpdater::onReplyFinish()
{
    qDebug() << "SFUpdater::onReplyFinish start ...";
    if(_state == ComicDataGetting)
    {
        _state = CoverImageGetting;
        _networkAccessor->get(_imageMap.keys());
        qDebug() << "SFUpdater:: comicCount = " << _comicCount;
        emit finish();
    }
    else if(_state == CoverImageGetting)
    {
        _state = Prepared;
        qDebug() << "SFUpdater:: coverCount = " << _coverCount;
        qDebug() << "SFUpdater::finish, counts = " << _comicCount;

        emit finish();
    }
}


int SFUpdater::getMaxPageNumber(const QString &content)
{
    qDebug() << "SFUpdate::getPageNumberGetting start ...";

    int pageNumber = 0;

    QRegExp pageNumExp("http://comic.sfacg.com/Catalog/"
                       "Default.aspx\\?PageIndex=(\\d+)");

    int pos = 0;
    while ((pos = pageNumExp.indexIn(content, pos)) != -1)
    {
        const int captureNumber = pageNumExp.cap(1).toInt();
        if(pageNumber < captureNumber)
            pageNumber = captureNumber;

        pos += pageNumExp.matchedLength();
    }

    //因為有bug，所以還要再加一頁
    pageNumber += 1;
    qDebug() << "SFUpdate::get pageNumber " << pageNumber;
    return pageNumber;
}

QStringList SFUpdater::getPageUrlList(const int &maxPageNumber)
{
    qDebug() << "SFUpdate::getPageUrlList start ...";

    QStringList pageUrlList;
    for(int i = 1; i <= maxPageNumber; i++)
    {
        pageUrlList.append("http://comic.sfacg.com/Catalog/Default.aspx?"
                       "PageIndex=" + QString::number(i));
    }

    return pageUrlList;
}

void SFUpdater::initialize()
{
    qDebug() << "QFUpdate::initialize start... ";
    _comicCount = _coverCount = 0;
    _comicInfoList.clear();
    _imageMap.clear();
}

void SFUpdater::processComicData(const QByteArray &content)
{
    qDebug() << "SFUpdater::processComicData start ...";

    const QString html(content);

    QRegExp regexp("<img src=\"([^\"]+)\"" //cover
                   "[^>]+></a></li>\\s+<li><strong class=\""
                   "F14PX\"><a href=\"/HTML/([^/]+)" //keyName
                   "[^>]+>([^<]+)" //name
                   "[^1]+1\">([^<]+)" //comicAuthor
                   "[^\\]]+[^>]+>([^<]+)" //comicType
                   "</a> /([^/]+)+/" //lastUpdated
                   " \\d+<br />([^<]+)" //description
                   );

    int pos = 0;
    while ((pos = regexp.indexIn(html, pos)) != -1)
    {
        ComicInfo info;
        qDebug() << regexp.cap(1);
        info.setKey(regexp.cap(2));
        info.setName(regexp.cap(3));
        info.setAuthor(regexp.cap(4));
        info.setType(regexp.cap(5));
        info.setLastUpdated(regexp.cap(6));
        info.setDescription(regexp.cap(7).simplified());

        qDebug() << "SFUpdater::" << info.getInfo();
        _comicInfoList.append(info);
        _imageMap[regexp.cap(1)] = _comicInfoList.count() - 1;

        pos += regexp.matchedLength();
        qDebug() << "SFUpdater::comicCount:" <<  ++_comicCount;
    }
}

void SFUpdater::processCoverImage(const QString &url,
                                  const QByteArray &content)
{
    qDebug() << "SFUpdater::processCoverImage start ...";
    QImage cover;
    if(!cover.loadFromData(content))
    {
        qDebug() << "SFUpdater::cover loading failed";
    }

    ComicInfo info = _comicInfoList[_imageMap[url]];
    info.setCover(cover);
    _comicInfoList[_imageMap[url]] = info;
    emit comicInfo(info);

    qDebug() << "SFUpdater::coverCount:" << ++_coverCount;
}




