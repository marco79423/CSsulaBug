#include "blcomicsitehandler.h"
#include "../networkaccessor.h"

#include <QEventLoop>

BLComicSiteHandler::BLComicSiteHandler(QObject *parent)
    :AComicSiteHandler(parent), _networkAccessor(new NetworkAccessor(this))
{
    connect(_networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)), this, SLOT(_getComicInfo(const int&, const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finishSignal(const int&)), this, SIGNAL(updateFinishedSignal()));
}

QList<StringPair> BLComicSiteHandler::getChapters(const QString &comicKey)
{

}

QStringList BLComicSiteHandler::getImageUrls(const QString &comicKey, const QString &chapterKey)
{

}

void BLComicSiteHandler::update()
{
    //取得所有漫畫列表的頁面
    const QString comicListPage = _networkAccessor->getDataImmediately("http://blmanhua.com/bllist/0/");

    //找到漫畫列表最後一頁
    QRegExp pageNumExp("部漫画 <b>1</b>/<b>(\\d+)</b>");
    pageNumExp.indexIn(comicListPage, 0);
    int maxPageNumber = pageNumExp.cap(1).toInt();

    QStringList allComicListPages;
    const QString pattern("http://blmanhua.com/bllist/0/%1/");
    for(int i = 1; i <= maxPageNumber; i++)
        allComicListPages.append(pattern.arg(i));

    //抓取所有漫畫列表
    _networkAccessor->get(allComicListPages);
}

void BLComicSiteHandler::_getComicInfo(const int &id, const QString &url, const QByteArray &data)
{
    Q_UNUSED(id)
    Q_UNUSED(url)

    QString html(data);
    QRegExp regexp("<a title='([^']+)' href='http://blmanhua.com/manhua/([^']+)'><img src='([^']+)'><br>[^<]+<span class='clw[12]'>\\[([^\\]]+)\\]");

    int pos = 0;
    while ((pos = regexp.indexIn(html, pos)) != -1)
    {
        StringHash comicInfo;
        comicInfo["site"] = "BL";
        comicInfo["coverUrl"] = regexp.cap(3);
        comicInfo["key"] = regexp.cap(2);
        comicInfo["name"] = _convertz.convertToTraditional(regexp.cap(1).simplified());
        comicInfo["author"] = "";
        comicInfo["type"] = "耽美類";
        comicInfo["lastUpdated"] = _convertz.convertToTraditional(regexp.cap(4).simplified());

        //qDebug() << "取得" << comicInfo;
        emit comicInfoSignal(comicInfo);

        pos += regexp.matchedLength();
    }
}
