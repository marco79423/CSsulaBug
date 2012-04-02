#include "sfdownloadpreparer.h"
#include <QtNetwork>
#include <QRegExp>
#include <QDebug>

SFDownloadPreparer::SFDownloadPreparer(QObject *parent) :
    QObject(parent), _state(Prepared)
{
    _networkAccessManager = new QNetworkAccessManager(this);
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onReply(QNetworkReply*)));
}

QStringList SFDownloadPreparer::getChapterNameList()
{
    if(!_state != Prepared) qCritical() << tr("SFDownloader:: 還沒準備好");
    return _chapterNameList;
}

QStringList SFDownloadPreparer::getUrlList(const QString &chapterName)
{
    if(!_state != Prepared) qCritical() << tr("SFDownloader:: 還沒準備好");
    return _urlListHash[chapterName];
}

void SFDownloadPreparer::prepare(const QString &key)
{
    initialize();

    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://comic.sfacg.com/HTML/%1/").arg(key)));

    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");

    qDebug() << tr("SFDownloadPreparer::發送要求至 ") << request.url();

    _state = ChapterNameListing;
    _networkAccessManager->get(request);
}

void SFDownloadPreparer::onReply(QNetworkReply *reply)
{
    if(reply->error())
    {
        qCritical() << tr("SFDownloadPreparer::") << reply->error();
        reply->deleteLater();
        return;
    }

    QString chapterName;
    if(_state == UrlListing)
    {
        QRegExp chapterExp("\\.sfacg\\.com/Utility/\\d+/(\\d+).js");
        chapterExp.indexIn(reply->url().toString());
        chapterName = chapterExp.cap(1);
    }


    switch(_state)
    {
    case ChapterNameListing://列出所有話
        listChapterName(reply->readAll());
        prepareListingUrl();
        break;
    case UrlListing://列出所有張圖
        listUrl(chapterName, reply->readAll());
        break;

    default:
        break;
    }

    reply->deleteLater();
}

void SFDownloadPreparer::initialize()
{
    _chapterNameList.clear();
    _comicID = -1;
    _comicType.clear();

    _urlListHash.clear();

    _checkList.clear();

    _state = Prepared;
}

void SFDownloadPreparer::listChapterName(const QString &content)
{
    //取得 ID
    QRegExp idExp("comicCounterID = (\\d+)");
    idExp.indexIn(content);
    _comicID = idExp.cap(1).toInt();
    qDebug() << "SFDownloadPreparer::取得 comicID " << _comicID;

    //取得 漫畫類型
    QRegExp typeExp("<a href=\"http://([^\"]+).sfacg.com/AllComic");
    typeExp.indexIn(content);
    _comicType = typeExp.cap(1);
    qDebug() << "SFDownloadPreparer::取得 comicType" << _comicType;

    //取得 話數名稱
    QRegExp chapterExp(
                QString("<a href=\"http://%1.sfacg.com/AllComic/%2/(\\d+j?)/")
                .arg(_comicType)
                .arg(_comicID));

    int pos = 0;
    while ((pos = chapterExp.indexIn(content, pos)) != -1)
    {
        _chapterNameList << chapterExp.cap(1);
        pos += chapterExp.matchedLength();
    }
    qDebug() << "SFDownloadPreparer::取得 chapterName "
             << _chapterNameList.join(", ");

    qDebug() << "SFDownloadPreparer::preprocess 結束";
}

void SFDownloadPreparer::prepareListingUrl()
{
    _state = UrlListing;
    _checkList = _chapterNameList;

    foreach(QString chapter, _chapterNameList)
    {
        QString url = QString("http://%1.sfacg.com/Utility/%2/%3.js")
                .arg(_comicType).arg(_comicID).arg(chapter);

        QNetworkRequest request(url);
        request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");

        qDebug() << tr("SFDownloadPreparer::發送要求至 ") << request.url();

        _networkAccessManager->get(request);
    }
}

void SFDownloadPreparer::listUrl(const QString &chapterName,
                                 const QString &content)
{
    qDebug() << "SFDownloadPreparer::準備下載 " << chapterName;
    QRegExp urlExp("picAy\\[(\\d+)\\] = \"([^\"]+)\"");

    int pos = 0;
    while ((pos = urlExp.indexIn(content, pos)) != -1)
    {
        _urlListHash[chapterName] << urlExp.cap(2);
        pos += urlExp.matchedLength();
    }

    qDebug() << "SFDownloadPreparer::取得 urlList "
             << _urlListHash[chapterName].join("\n");

    //檢查下載是否完結
    _checkList.removeAll(chapterName);
    if(_checkList.empty())
    {
        qDebug() << "SFDownloadPreparer:: 準備完成！";
        _state = Prepared;
        emit finish();
    }
}
