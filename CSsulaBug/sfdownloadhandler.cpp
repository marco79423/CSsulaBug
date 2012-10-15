#include "sfdownloadhandler.h"
#include "networkaccessor.h"
#include <QNetworkReply>
#include <QDebug>

SFDownloadHandler::SFDownloadHandler(QObject *parent) :
    DownloadHandler(parent), _currentState(NothingDoing)
{
    _networkAccessor = new NetworkAccessor(this);
    _downloader = new Downloader(this);
    _setConnection();
}


bool SFDownloadHandler::isReady() const
{
    return _currentState == NothingDoing;
}

void SFDownloadHandler::download(const QString &key, const QString &dstDir)
{
    switch(_currentState)
    {
    case NothingDoing:
        qDebug() << "SFDownloadHandler:download:開始下載" << key;
        _key = key;
        _dstDir = dstDir;
        _startProcess(ChapterUrlListing);
        break;
    default:
        qDebug() << "SFDownloadHandler:download:錯誤的狀態" << _currentState;
        break;
    }
}

void SFDownloadHandler::_onAccessorReply(const int &id,
                                         QNetworkReply *networkReply)
{
    const QString url = networkReply->url().toString();
    const QString html = networkReply->readAll();

    switch(_currentState)
    {
    case ChapterUrlListing:
        _getComicName(html);
        _listChapters(html);
        break;
    case TaskMaking:
        _makeTask(url, html);
        break;
    default:
        qDebug() << "SFDownloadHandler:_onAccessorReply:錯誤的狀態"
                 << _currentState;
        break;
    }
}

void SFDownloadHandler::_onAccessorFinish(const int &id)
{
    switch(_currentState)
    {
    case ChapterUrlListing:
        _startProcess(TaskMaking);
        break;
    case TaskMaking:
        _startProcess(Downloading);
        break;
    default:
        qDebug() << "SFDownloadHandler:_onAccessorFinish:錯誤的狀態"
                 << _currentState;
        break;
    }
}

void SFDownloadHandler::_onDownloaderFinish()
{
    _currentState = NothingDoing;
    emit finish();
}

void SFDownloadHandler::_setConnection()
{
    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&)),
            SLOT(_onAccessorFinish(const int&)));
    connect(_downloader, SIGNAL(info(const QHash<QString,QString>&)),
            SIGNAL(info(const QHash<QString,QString>&)));
}

void SFDownloadHandler::_startProcess(const SFDownloadHandler::State &state)
{
    qDebug() << "SFDownloadHandler:_startProcess:開始執行 " << state << "狀態";
    switch(state)
    {
    case ChapterUrlListing:
        _currentState = ChapterUrlListing;
        _networkAccessor->get(QString("http://comic.sfacg.com/HTML/%1/")
                              .arg(_key));
        break;
    case TaskMaking:
        _currentState = TaskMaking;
        _networkAccessor->get(_chapterUrlList);
        break;
    case Downloading:
        _currentState = Downloading;
        _downloader->download(_task);
        break;
    default:
        qCritical() << "SFDownloadHandler:_startProcess:錯誤的狀態 " << state;
    }
}

void SFDownloadHandler::_getComicName(const QString &html)
{
    QRegExp nameExp("<b class=\"F14PX\">([^<]+)</b>");
    nameExp.indexIn(html);
    _comicName = nameExp.cap(1);
    qDebug() << "SFDownloadHandler:_getComicName:取得漫畫名稱 " << _comicName;
}

void SFDownloadHandler::_listChapters(const QString &html)
{
    //取得 ID
    QRegExp idExp("comicCounterID = (\\d+)");
    idExp.indexIn(html);
    int comicID = idExp.cap(1).toInt();
    qDebug() << "取得 comicID " << comicID;

    //取得 漫畫種類(網站自己的分法)
    QRegExp typeExp("<a href=\"http://([^\"]+).sfacg.com/AllComic");
    typeExp.indexIn(html);
    QString comicType = typeExp.cap(1);
    qDebug() << "取得 comicType " << comicType;

    //取得話數
    QRegExp chapterExp(QString("<a href=\"http://%1.sfacg.com/AllComic"
                               "/%2/(\\d+j?)/").arg(comicType).arg(comicID));
    qDebug() << QString("<a href=\"http://%1.sfacg.com/AllComic"
                        "/%2/(\\d+j?)/").arg(comicType).arg(comicID);
    int pos = 0;
    while ((pos = chapterExp.indexIn(html, pos)) != -1)
    {
        QString chapterUrl = QString("http://%1.sfacg.com/Utility/%2/%3.js")
                .arg(comicType).arg(comicID).arg(chapterExp.cap(1));

        _chapterUrlList.append(chapterUrl);
        qDebug() << "取得 chapterUrl " << chapterUrl;
        pos += chapterExp.matchedLength();
    }
}

void SFDownloadHandler::_makeTask(const QString &url, const QString &html)
{
    //取得 chapter
    QRegExp chapterExp("\\.sfacg\\.com/Utility/\\d+/(\\d+j?).js");
    chapterExp.indexIn(url);
    QString chapter = chapterExp.cap(1);

    //取得 imageUrl
    QRegExp urlExp("picAy\\[(\\d+)\\] = \"([^\"]+)\"");

    int pos = 0;
    while ((pos = urlExp.indexIn(html, pos)) != -1)
    {
        int imageNum = urlExp.cap(1).toInt();
        QString imageUrl = urlExp.cap(2);
        QString path = QString("%1/%2/%3/%4.%5")
                .arg(_dstDir).arg(_comicName).arg(chapter)
                .arg(imageNum, 3, 10, QChar('0'))
                .arg(imageUrl.right(3));

        _task[imageUrl] = path;
        pos += urlExp.matchedLength();
    }
}


void SFDownloadHandler::d_test()
{
    /*
      * 測試
      */
    download("FSJII", "漫畫");
}
