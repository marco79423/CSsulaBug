#include "blcomicsitehandler.h"
#include "../networkaccessor.h"

#include <QUrlQuery>
#include <QEventLoop>

BLComicSiteHandler::BLComicSiteHandler(QObject *parent)
    :AComicSiteHandler(parent), _networkAccessor(new NetworkAccessor(this))
{
    connect(_networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)), this, SLOT(_getComicInfo(const int&, const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finishSignal(const int&)), this, SIGNAL(updateFinishedSignal()));
}

QString BLComicSiteHandler::getComicSiteName() const
{
    /*
     * http://blmanhua.com/
     */
    return "耽美漫畫";
}

QList<StringPair> BLComicSiteHandler::getChapters(const QString &comicKey)
{
    const QString html = _networkAccessor->getDataImmediately(QString("http://blmanhua.com/manhua/%1/").arg(comicKey));

    //取得話數
    QRegExp chapterExp(QString("<a title='[^']+'[^h]*href='([^']+)' target=_blank>([^<]+)"));

    QList<StringPair> chapters;
    int pos = 0;
    while ((pos = chapterExp.indexIn(html, pos)) != -1)
    {
        QString chapterName = _convertz.convertToTraditional(chapterExp.cap(2));
        QString chapterUrl = chapterExp.cap(1);

        //去掉話數名稱多餘或不常用的字
        QRegExp chapterNameExp(QString("([^ ]*\\d+ ?[卷集])"));
        if(chapterNameExp.indexIn(chapterName, 0) != -1)
        {
            chapterName = chapterNameExp.cap(1);
            chapterName.replace(" ", "");
            chapterName.replace("集", "話");
        }

        chapters.append(StringPair(chapterName, chapterUrl));
        pos += chapterExp.matchedLength();
    }

    return chapters;
}

QStringList BLComicSiteHandler::getImageUrls(const QString &comicKey, const QString &chapterKey)
{
    Q_UNUSED(comicKey)

    const QString url = chapterKey;

    //取得 serverUrl
    /*Qt 5.3.1 的 QUrlQuery 似乎有 Bug
    QUrlQuery urlQuery(url);
    qDebug() << urlQuery.queryItemValue("s");*/

    QRegExp urlExp("s=(\\d+)");
    urlExp.indexIn(url);
    const QString serverUrl = _getServerUrl(urlExp.cap(1).toInt());

    //取得 encrypted_code
    const QString html = _networkAccessor->getDataImmediately(url);
    QRegExp encryptedCodeExp("var PicListUrl = \"([^\"]+)\"");
    encryptedCodeExp.indexIn(html);
    QString encryptedCode = encryptedCodeExp.cap(1).toUtf8();


    //code = "tazsicoewrn"
    const QString replaceCode = "tazsicoewr";
    const QChar splitCode = 'n';

    //用 replaceCode 對應的 index 取代字串
    for(int i=0; i < replaceCode.size(); i++)
    {
        encryptedCode.replace(replaceCode[i], QString::number(i));
    }

    //用 split_code 切割字串，會切出許多數字
    QList<int> numList;
    QStringList splitedString = encryptedCode.split(splitCode);
    for(int i=0; i < splitedString.size(); i++)
    {
        numList << splitedString[i].toInt();
    }

    //把這些數字當成 ASCII 再轉成字串相連
    QString imageListString;
    foreach(int num, numList)
    {
        imageListString += QChar(num);
    }

    //再將這些字串用 | 切開
    QStringList imageList = imageListString.split("|");


    //取得 imageUrl
    QStringList imageUrls;
    foreach(QString imageString, imageList)
    {
        imageUrls << serverUrl + imageString;
    }

    return imageUrls;
}

QString BLComicSiteHandler::getReferer() const
{
    return "http://hh.3gmanhua.com/";
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
        comicInfo["site"] = getComicSiteName();
        comicInfo["coverUrl"] = regexp.cap(3);
        comicInfo["key"] = regexp.cap(2);
        comicInfo["name"] = _convertz.convertToTraditional(regexp.cap(1).simplified());
        comicInfo["author"] = "";
        comicInfo["type"] = "耽美類";

        comicInfo["updateStatus"] = _convertz.convertToTraditional(regexp.cap(4).simplified());

        //如果只有數字，補上 話(卷)
        QRegExp updateStatusExp("\\d+");
        if(updateStatusExp.indexIn(comicInfo["updateStatus"], 0) != -1)
        {
            comicInfo["updateStatus"] += "話(卷)";
        }

        //qDebug() << "取得" << comicInfo;
        emit comicInfoSignal(comicInfo);

        pos += regexp.matchedLength();
    }
}

QString BLComicSiteHandler::_getServerUrl(const int serverIndex)
{
    QMap<int, QString> serverList;
    serverList[0]="http://cdn2.3348.net:9292/dm01/";
    serverList[1]="http://cdn2.3348.net:9292/dm02/";
    serverList[2]="http://cdn2.3348.net:9292/dm03/";
    serverList[3]="http://cdn2.3348.net:9292/dm04/";
    serverList[4]="http://cdn2.3348.net:9292/dm05/";
    serverList[5]="http://cdn2.3348.net:9292/dm06/";
    serverList[6]="http://cdn2.3348.net:9292/dm07/";
    serverList[7]="http://cdn2.3348.net:9292/dm08/";
    serverList[8]="http://cdn2.3348.net:9292/dm09/";
    serverList[9]="http://cdn2.3348.net:9292/dm10/";
    serverList[10]="http://cdn2.3348.net:9292/dm11/";
    serverList[11]="http://cdn2.3348.net:9292/dm12/";
    serverList[12]="http://cdn2.3348.net:9292/dm13/";
    serverList[13]="http://8.8.8.8:99/dm14/"; //怎麼可能？
    serverList[14]="http://cdn2.3348.net:9292/dm15/";
    serverList[15]="http://cdn2.3348.net:9292/dm16/";
    return serverList[serverIndex - 1];
}
