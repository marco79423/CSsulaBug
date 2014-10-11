#include "sfcomicsitehandler.h"
#include "../networkaccessor.h"

#include <QEventLoop>

SFComicSiteHandler::SFComicSiteHandler(QObject *parent)
    :AComicSiteHandler(parent), _networkAccessor(new NetworkAccessor(this))
{
    connect(_networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)), this, SLOT(_getComicInfo(const int&, const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finishSignal(const int&)), this, SIGNAL(updateFinishedSignal()));
}

QString SFComicSiteHandler::getComicSiteName() const
{
    /*
     * http://comic.sfacg.com
     */
    return "SF 互動傳媒網";
}

QList<StringPair> SFComicSiteHandler::getChapters(const QString &comicKey)
{
    const QString html = _networkAccessor->getDataImmediately(QString("http://comic.sfacg.com/HTML/%1/").arg(comicKey));

    //取得 ID
    QRegExp idExp("comicCounterID = (\\d+)");
    idExp.indexIn(html);
    int comicID = idExp.cap(1).toInt();

    //取得話數
    QRegExp chapterExp(QString("<a href=\"/HTML/%1/(\\d+j?)/[^>]*>(<font color=red>)?([^<]+)").arg(comicKey));

    QList<StringPair> chapters;
    int pos = 0;
    while ((pos = chapterExp.indexIn(html, pos)) != -1)
    {
        QString chapterName = _convertz.convertToTraditional(chapterExp.cap(3));
        QString chapterUrl = QString("http://comic.sfacg.com/Utility/%1/%2.js").arg(comicID).arg(chapterExp.cap(1));

        chapters.append(StringPair(chapterName, chapterUrl));
        pos += chapterExp.matchedLength();
    }

    return chapters;
}

QStringList SFComicSiteHandler::getImageUrls(const QString &comicKey, const QString &chapterKey)
{
    Q_UNUSED(comicKey)

    const QString url = chapterKey;
    const QString html = _networkAccessor->getDataImmediately(url);

    //取得 host
    QRegExp hostExp("var hosts = \\[\"([^\"]+)");
    hostExp.indexIn(html);
    QString host = hostExp.cap(1);
    qDebug() << "取得 host " << host;

    //取得 imageUrl
    QStringList imageUrls;

    QRegExp urlExp("picAy\\[\\d+\\] = \"([^\"]+)\"");
    int pos = 0;
    while ((pos = urlExp.indexIn(html, pos)) != -1)
    {
        QString imageUrl = host + urlExp.cap(1);

        imageUrls.append(imageUrl);
        pos += urlExp.matchedLength();
    }

    return imageUrls;
}

void SFComicSiteHandler::update()
{
    //取得所有漫畫列表的頁面
    const QString catalogPage = _networkAccessor->getDataImmediately("http://comic.sfacg.com/Catalog/");

    //找到漫畫列表最後一頁
    int maxPageNumber = 0;
    QRegExp pageNumExp("http://comic.sfacg.com/Catalog/[dD]efault.aspx\\?PageIndex=(\\d+)");
    int pos = 0;
    while ((pos = pageNumExp.indexIn(catalogPage, pos)) != -1)
    {
        const int captureNumber = pageNumExp.cap(1).toInt();
        if(maxPageNumber < captureNumber)
            maxPageNumber = captureNumber;

        pos += pageNumExp.matchedLength();
    }
    //因為有bug，所以還要再加一頁
    maxPageNumber += 1;

    QStringList allComicListPages;
    const QString pattern("http://comic.sfacg.com/Catalog/default.aspx?PageIndex=%1");
    for(int i = 1; i <= maxPageNumber; i++)
        allComicListPages.append(pattern.arg(i));

    //抓取所有漫畫列表
    _networkAccessor->get(allComicListPages);
}

void SFComicSiteHandler::_getComicInfo(const int& id, const QString& url, const QByteArray& data)
{
    Q_UNUSED(id)
    Q_UNUSED(url)

    QString html(data);
    QRegExp regexp("<img src=\"([^\"]+)\""  //cover
                   "[^>]+></a></li>\\s+<li><strong class=\""
                   "F14PX\"><a href=\"/HTML/([^/]+)" //keyName
                   "[^>]+>([^<]+)" //name
                   "[^1]+1\">([^<]+)" //comicAuthor
                   "[^\\]]+[^>]+>([^<]+)" //comicType
                   "</a> /([^/]+)+/" //updateStatus
                   " \\d+<br />([^<]+)" //description
                   );
    //QRegExp regexp("<img src=\"([^\"]+)\"[^>]+></a></li>\\s+<li><strong class=\"F14PX\"><a href=\"/HTML/([^/]+)[^>]+>([^<]+)[^1]+1\">([^<]+)[^\\]]+[^>]+>([^<]+)</a> /([^/]+)+/ \\d+<br />([^<]+)");

    int pos = 0;
    while ((pos = regexp.indexIn(html, pos)) != -1)
    {
        StringHash comicInfo;
        comicInfo["site"] = getComicSiteName();
        comicInfo["coverUrl"] = regexp.cap(1);
        comicInfo["key"] = regexp.cap(2);
        comicInfo["name"] = _convertz.convertToTraditional(regexp.cap(3).simplified());
        comicInfo["author"] = _convertz.convertToTraditional(regexp.cap(4).simplified());
        comicInfo["type"] = _convertz.convertToTraditional(regexp.cap(5).simplified());
        comicInfo["updateStatus"] = _convertz.convertToTraditional(regexp.cap(6).simplified());
        //updateInfo["description"] = regexp.cap(7).simplified();

        //qDebug() << "取得" << comicInfo;
        emit comicInfoSignal(comicInfo);

        pos += regexp.matchedLength();
    }
}
