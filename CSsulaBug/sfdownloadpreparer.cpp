#include "sfdownloadpreparer.h"
#include "networkaccessor.h"
#include <QtNetwork>
#include <QRegExp>
#include <QDebug>

SFDownloadPreparer::SFDownloadPreparer(QObject *parent) :
    QObject(parent), _state(Prepared)
{
    _networkAccessor = new NetworkAccessor(this);
    connect(_networkAccessor,
            SIGNAL(oneReply(const QString&, const QByteArray&)),
            SLOT(onOneReply(const QString&, const QByteArray&)));
    connect(_networkAccessor, SIGNAL(finish()), SLOT(onReplyFinish()));
}

QStringList SFDownloadPreparer::getChapterNameList()
{
    if(_state != Prepared) qCritical() << tr("SFDownloader:: isn't prepared");
    return _chapterNameList;
}

QStringList SFDownloadPreparer::getUrlList(const QString &chapterName)
{
    if(_state != Prepared) qCritical() << tr("SFDownloader:: isn't prepared");
    return _urlListHash[chapterName];
}

void SFDownloadPreparer::prepare(const QString &key)
{
    qDebug() << "SFDownloadPreparer::prepare start ...";
    initialize();

    _state = ChapterNameListing;
    _networkAccessor->get(QString("http://comic.sfacg.com/HTML/%1/").arg(key));
}

void SFDownloadPreparer::onOneReply(const QString &url,
                                    const QByteArray &content)
{
    if(_state == ChapterNameListing) //列出所有話
    {
        listChapterName(content);
    }
    else if(_state == UrlListing) //列出所有張圖
    {
        QRegExp chapterExp("\\.sfacg\\.com/Utility/\\d+/(\\d+j?).js");
        chapterExp.indexIn(url);
        QString chapterName = chapterExp.cap(1);

        listUrl(chapterName, content);
    }
}

void SFDownloadPreparer::onReplyFinish()
{
    if(_state == UrlListing)
    {
        qDebug() << "SFDownloadPreparer:: 準備完成！";
        _state = Prepared;
        emit finish();
    }
}

void SFDownloadPreparer::initialize()
{
    _chapterNameList.clear();
    _comicID = -1;
    _comicType.clear();

    _urlListHash.clear();
    _state = Prepared;
}

void SFDownloadPreparer::listChapterName(const QString &content)
{
    //取得 ID
    QRegExp idExp("comicCounterID = (\\d+)");
    idExp.indexIn(content);
    _comicID = idExp.cap(1).toInt();
    qDebug() << "SFDownloadPreparer::取得 comicID " << _comicID;

    //取得 漫畫種類(網站自己的分法)
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
        qDebug() << "SFDownloadPreparer:: get chapterName " << chapterExp.cap(1);
        _chapterNameList << chapterExp.cap(1);
        pos += chapterExp.matchedLength();
    }

    QStringList chapterUrlList;
    foreach(QString chapter, _chapterNameList)
    {
        chapterUrlList << QString("http://%1.sfacg.com/Utility/%2/%3.js")
                .arg(_comicType).arg(_comicID).arg(chapter);
    }

    _state = UrlListing;
    _networkAccessor->get(chapterUrlList);
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
}
