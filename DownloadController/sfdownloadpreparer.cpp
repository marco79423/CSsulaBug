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
    if(!_state != Done) qCritical() << tr("SFDownloader:: 還沒準備好");
    return _chapterNameList;
}

QStringList SFDownloadPreparer::getUrlList(const QString &chapterName)
{
    if(!_state != Done) qCritical() << tr("SFDownloader:: 還沒準備好");
    return _urlListHash[chapterName];
}

void SFDownloadPreparer::download(const QString &key)
{
    initialize();

    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://comic.sfacg.com/HTML/%1/").arg(key)));

    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");

    qDebug() << tr("SFDownloadPreparer::發送要求至 ") << request.url();

    _networkAccessManager->get(request);
}

void SFDownloadPreparer::onReply(QNetworkReply *reply)
{
    if(reply->error())
    {
        qCritical() << tr("SFDownloadPreparer::") << reply->error();
        return;
    }

    switch(_state)
    {
    case Prepared://前置準備
        listChapterName(reply->readAll());
        _state = ChapterNameListing;
        break;
    case ChapterNameListing://列出所有話
        break;
    case UrlListing://列出所有張圖
        break;
    case Done:
        break;
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
    qDebug() << content;
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
