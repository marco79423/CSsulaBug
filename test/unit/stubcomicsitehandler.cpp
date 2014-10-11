#include "stubcomicsitehandler.h"
#include <QNetworkReply>
#include <QStringList>
#include <QTimer>


QString StubComicSiteHandler::getComicSiteName() const
{
    return "Stub ComicSiteHandler";
}

QList<StringPair> StubComicSiteHandler::getChapters(const QString &comicKey)
{
    if(comicKey == "key0")
        return QList<StringPair>() << StringPair("chapter0", "url0");
    else if(comicKey == "key1")
        return QList<StringPair>() << StringPair("chapter0", "url0") << StringPair("chapter1", "url1");
    else if(comicKey == "key2")
        return QList<StringPair>() << StringPair("chapter0", "url0") << StringPair("chapter1", "url1") << StringPair("chapter2", "url2");
    return QList<StringPair>();
}

QStringList StubComicSiteHandler::getImageUrls(const QString &comicKey, const QString &chapterKey)
{
    if(comicKey == "key0")
        return QStringList() << chapterKey;
    else if(comicKey == "key1")
        return QStringList() << chapterKey << chapterKey;
    else if(comicKey == "key2")
        return QStringList() << chapterKey << chapterKey << chapterKey;
    return QStringList();
}

void StubComicSiteHandler::update()
{
    for(int i=0; i< 3; i++)
    {
        QTimer::singleShot(i * 100, this, SLOT(_onUpdate()));
    }
}

void StubComicSiteHandler::_onUpdate()
{
    static int i=0;

    StringHash comicInfo;
    comicInfo["site"] = getComicSiteName();
    comicInfo["coverUrl"] = QString("coverUrl%1").arg(i);
    comicInfo["key"] = QString("key%1").arg(i);
    comicInfo["name"] = QString("name%1").arg(i);
    comicInfo["author"] = QString("author%1").arg(i);
    comicInfo["type"] = QString("type%1").arg(i);
    comicInfo["updateStatus"] = QString("updateStatus%1").arg(i);
    emit comicInfoSignal(comicInfo);

    if(i == 2)
    {
        i=0;
        emit updateFinishedSignal();
    }

    i+=1;
}
