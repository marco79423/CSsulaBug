#include "sfupdater.h"
#include "networkaccessor.h"
#include <QRegExp>
#include <QDebug>

SFUpdater::SFUpdater(QObject *parent) :
    QObject(parent), _state(Prepared)
{
    _networkAccessor = new NetworkAccessor(this);
    connect(_networkAccessor, SIGNAL(oneReply(const QString&)),
            SLOT(onOneReply(const QString&)));
    connect(_networkAccessor, SIGNAL(finish()), SLOT(onReplyFinish()));
}

SFUpdater::State SFUpdater::getState() const
{
    return _state;
}

void SFUpdater::update()
{
    qDebug() << "SFUpdate::update start ...";
    if(_state != Prepared) qCritical() << "SFUpdater::isn't prepared";

    qDebug() << "SFUpdate::change state to PageNumberGetting";
    _state = PageNumberGetting;

    qDebug() << "SFUpdate::get http://comic.sfacg.com/Catalog/";
    _networkAccessor->get("http://comic.sfacg.com/Catalog/");
}

void SFUpdater::onOneReply(const QString &content)
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
}

void SFUpdater::onReplyFinish()
{
    qDebug() << "SFUpdater::onReplyFinish start ...";
    if(_state == ComicDataGetting)
    {
        _state = Prepared;
        qDebug() << "SFUpdater::finish";
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

void SFUpdater::processComicData(const QString &content)
{
    qDebug() << "SFUpdater::processComicData start ...";

    QRegExp regexp("(?:<a href=\"/HTML/)([^/]+)" //keyName
                   ".+(?:orange_link2\">)([^<]+)" //name
                   "(?:.|\n)+(?:Blue_link1\">)([^<]+)" //comicAuthor
                   "(?:.|\n)+(?:Blue_link1\">)([^<]+)" //comicType
                   "</a> /([^/]+)+/" //lastUpdated
                   " \\d+<br />\\s+([^<]+)"
                   );
    //(?:Blue_link1\">)([^<]+)
                    //"(?:.|\n)+?(?:Blue_link1">)([^<]+) \/([^\/]+)

    int pos = 0;
    while ((pos = regexp.indexIn(content, pos)) != -1)
    {
        qDebug() << regexp.cap(1) << regexp.cap(2) << regexp.cap(3)
                 << regexp.cap(4) << regexp.cap(5) << regexp.cap(6);
        pos += regexp.matchedLength();
    }
}


/*

void SFUpdater::processKeyNameListing(const QString &content)
{
    qDebug() << "SFUpdater::processKeyNameList start ...";

    //<li><strong class="F14PX"><a href="/HTML/XINF/"
    QRegExp comicExp();
    int pos = 0;
    while ((pos = comicExp.indexIn(content, pos)) != -1)
    {
        const QString comicUrl =
                "http://comic.sfacg.com/HTML/" + comicExp.cap(1);

       // qDebug() << "SFUpdater:: get " << comicUrl;
        _comicUrlList.append(comicUrl);

        pos += comicExp.matchedLength();
    }
}

void SFUpdater::processComicPageGetting(const QString &content)
{
    qDebug() << "SFUpdater::processComicPageGetting start ...";
    QRegExp keyNameExp("var folderName = '([^']+)';");
    QRegExp comicNameExp("<b class=\"F14PX\">([^>]+)</b>");
    QRegExp comicTypeExp("<li>漫画类型：[^>]+>([^<]+)");
    QRegExp comicAuthorExp("<li>作　　者：[^>]+>([^<]+)");
    QRegExp lastUpdatedExp("<li>更新时间：([^<]+)");
    QRegExp descriptionExp();

}

*/

