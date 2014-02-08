#include "sfdownloadhandler.h"
#include "networkaccessor.h"
#include <QNetworkReply>
#include <QDebug>
#include <QDir>

SFDownloadHandler::SFDownloadHandler(QObject *parent) :
    DownloadHandler(parent), _currentState(NothingDoing)
{
    _networkAccessor = new NetworkAccessor(this);
    _downloader = new Downloader(this);

    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&)),
            SLOT(_onAccessorFinish(const int&)));
    connect(_downloader, SIGNAL(info(const QHash<QString,QString>&)),
            SLOT(_onDownloaderInfo(const QHash<QString,QString>&)));
    connect(_downloader, SIGNAL(finish()), SIGNAL(finish()));
}


bool SFDownloadHandler::isReady() const
{
    return _currentState == NothingDoing;
}

void SFDownloadHandler::download(const QString &key, const QString &dstDir)
{
    if(isReady())
    {
        qDebug() << "SFDownloadHandler:download:開始下載" << key;
        _clear();
        _taskInfo["key"] = key;
        _taskInfo["dstDir"] = dstDir;
        _startProcess(ChapterUrlListing);
    }
    else
        qDebug() << "SFDownloadHandler:download:暫時不能下載" << _currentState;
}

void SFDownloadHandler::_onAccessorReply(const int &id,
                                         QNetworkReply *networkReply)
{
    const QString url = networkReply->url().toString();
    const QString html = networkReply->readAll();

    switch(_currentState)
    {
    case ChapterUrlListing: _getComicName(html); _listChapters(html); break;
    case TaskMaking: _makeTask(url, html); break;
    case Downloading: break;
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
    case ChapterUrlListing: _startProcess(TaskMaking); break;
    case TaskMaking: _startProcess(Downloading); break;
    case Downloading: break;
    default:
        qDebug() << "SFDownloadHandler:_onAccessorFinish:錯誤的狀態"
                 << _currentState;
        break;
    }
}

void SFDownloadHandler::_onDownloaderInfo(
        const QHash<QString, QString> downloaderInfo)
{
    //完成進度
    int done = _taskInfo["done"].toInt() + 1;
    int sum = _task.size();
    float progress = float(done) / sum * 100;

    //新增進度資訊
    _taskInfo["done"] =  QString::number(done);

    QHash<QString, QString> newInfo = downloaderInfo;
    newInfo["progress"] = QString::number(progress);

    qDebug() << "SFDownloadHandler:_onDownloaderInfo:" << newInfo;
    emit info(newInfo);
}

void SFDownloadHandler::_onDownloaderFinish()
{
    _clear();
    _currentState = NothingDoing;
    emit finish();
}

void SFDownloadHandler::_clear()
{
    _taskInfo.clear();
    _chapterUrlList.clear();
    _task.clear();
}

void SFDownloadHandler::_startProcess(const SFDownloadHandler::State &state)
{
    qDebug() << "SFDownloadHandler:_startProcess:開始 " << state << "狀態";
    _currentState = state;
    switch(state)
    {
    case ChapterUrlListing:
        _networkAccessor->get(QString("http://comic.sfacg.com/HTML/%1/")
                              .arg(_taskInfo["key"]));
        break;
    case TaskMaking:
        _networkAccessor->get(_chapterUrlList);
        break;
    case Downloading:
        _taskInfo["done"] = QString::number(0);
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
    _taskInfo["comicName"] = nameExp.cap(1);
    qDebug() << "SFDownloadHandler:_getComicName:取得漫畫名稱 " << _taskInfo["comicName"];
}

void SFDownloadHandler::_listChapters(const QString &html)
{
    //取得 ID
    QRegExp idExp("comicCounterID = (\\d+)");
    idExp.indexIn(html);
    int comicID = idExp.cap(1).toInt();
    qDebug() << "取得 comicID " << comicID;

    //取得話數
    QRegExp chapterExp(QString("<a href=\"/HTML/%1/(\\d+j?)/").arg(_taskInfo["key"]));
    qDebug() << QString("<a href=\"/HTML/%1/(\\d+j?)/").arg(_taskInfo["key"]);

    int pos = 0;
    while ((pos = chapterExp.indexIn(html, pos)) != -1)
    {
        QString chapterUrl = QString("http://comic.sfacg.com/Utility/%1/%2.js")
                .arg(comicID).arg(chapterExp.cap(1));

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

    //取得 host
    QRegExp hostExp("var hosts = \\[\"([^\"]+)");
    hostExp.indexIn(html);
    QString host = hostExp.cap(1);
    qDebug() << "取得 host " << host;

    //取得 imageUrl
    QRegExp urlExp("picAy\\[(\\d+)\\] = \"([^\"]+)\"");
    int pos = 0;
    while ((pos = urlExp.indexIn(html, pos)) != -1)
    {
        int imageNum = urlExp.cap(1).toInt();
        QString imageUrl = host + urlExp.cap(2);
        QString path = QString("%1/%2/%3/%4.%5")
                .arg(_taskInfo["dstDir"]).arg(_taskInfo["comicName"])
                .arg(chapter).arg(imageNum, 3, 10, QChar('0'))
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
    download("CANVA", "漫畫");
}
