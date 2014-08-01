#include "sfupdatehandler.h"
#include "networkaccessor.h"

#include <QNetworkReply>
#include <QDebug>

SFUpdateHandler::SFUpdateHandler(QObject *parent) :
    AUpdateHandler(parent), _currentState(NothingDoing)
{
    _networkAccessor = new NetworkAccessor(this);

    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&, const bool&)),
            SLOT(_onAccessorFinish(const int&, const bool&)));
}

bool SFUpdateHandler::isReady()
{
    return _currentState == NothingDoing;
}

void SFUpdateHandler::update()
{
    /*
      *若狀態為 NothingDoing 就更新線上內容，並會以 signal 的形式回傳訊息，
      *若狀態不為 NothingDoing 便什麼也不做。
      */
    if(isReady())
    {
        qDebug() << "SFUpdateHandler:update:開始更新";
        _clear();
        _startProcess(ALLPageUrlListGetting);
    }
    else
        qDebug() << "SFUpdateHandler:update:現在狀態還不能更新";
}


void SFUpdateHandler::_onAccessorReply(const int &id, QNetworkReply *networkReply)
{
    const QString html = networkReply->readAll();

    switch(_currentState)
    {
    case ALLPageUrlListGetting: _getPageUrl(html); break;
    case ComicInfoGetting: _getComicInfo(html); break;
    default:
        qCritical() << "SFUpdateHandler:_onAccessorReply:錯誤的狀態" << _currentState;
        break;
    }
}

void SFUpdateHandler::_onAccessorFinish(const int &id, const bool&error)
{
    switch(_currentState)
    {
    case ALLPageUrlListGetting: _startProcess(ComicInfoGetting); break;
    case ComicInfoGetting: _startProcess(Finishing); break;
    default: break;
    }
}

void SFUpdateHandler::_clear()
{
    _allPageUrlList.clear();
}

void SFUpdateHandler::_startProcess(const State &state)
{
    qDebug() << "SFUpdateHandler:_startProcess:開始 " << state << "狀態";

    _currentState = state;
    switch(state)
    {
    case ALLPageUrlListGetting:
        _networkAccessor->get("http://comic.sfacg.com/Catalog/");
        break;
    case ComicInfoGetting:
        _networkAccessor->get(_allPageUrlList);
        break;
    case Finishing:
        _clear();
        _currentState = NothingDoing;
        qDebug() << "SFUpdateHandler:_startProcess:下載完成";
        emit finish();
        break;
    default:
        qCritical() << "SFUpdateHandler:_startProcess:錯誤的狀態 " << state;
        break;
    }
}

void SFUpdateHandler::_getPageUrl(const QString &html)
{
    qDebug() << "SFUpdateHandler::_getPageUrl: 截取所有頁數的 url";
    int maxPageNumber = 0;

    //找到最後一頁
    QRegExp pageNumExp("http://comic.sfacg.com/Catalog/[dD]efault.aspx\\?PageIndex=(\\d+)");
    int pos = 0;
    while ((pos = pageNumExp.indexIn(html, pos)) != -1)
    {
        const int captureNumber = pageNumExp.cap(1).toInt();
        if(maxPageNumber < captureNumber)
            maxPageNumber = captureNumber;

        pos += pageNumExp.matchedLength();
    }

    //因為有bug，所以還要再加一頁
    maxPageNumber += 1;

    const QString pattern("http://comic.sfacg.com/Catalog/default.aspx?PageIndex=%1");
    for(int i = 1; i <= maxPageNumber; i++)
        _allPageUrlList.append(pattern.arg(i));
}

void SFUpdateHandler::_getComicInfo(const QString &html)
{
	qDebug() << "SFUpdateHandler:_getComicInfo: 截取頁面上所有漫畫資訊";

	/*
    QRegExp regexp("<img src=\"([^\"]+)\""  //cover
                   "[^>]+></a></li>\\s+<li><strong class=\""
                   "F14PX\"><a href=\"/HTML/([^/]+)" //keyName
                   "[^>]+>([^<]+)" //name
                   "[^1]+1\">([^<]+)" //comicAuthor
                   "[^\\]]+[^>]+>([^<]+)" //comicType
                   "</a> /([^/]+)+/" //lastUpdated
                   " \\d+<br />([^<]+)" //description
                   );*/
	QRegExp regexp("<img src=\"([^\"]+)\"[^>]+></a></li>\\s+<li><strong class=\"F14PX\"><a href=\"/HTML/([^/]+)[^>]+>([^<]+)[^1]+1\">([^<]+)[^\\]]+[^>]+>([^<]+)</a> /([^/]+)+/ \\d+<br />([^<]+)");

    int pos = 0;
    while ((pos = regexp.indexIn(html, pos)) != -1)
    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = regexp.cap(1);
        updateInfo["key"] = regexp.cap(2);
        updateInfo["name"] = _convertz.convertToTraditional(regexp.cap(3));
        updateInfo["author"] = _convertz.convertToTraditional(regexp.cap(4));
        updateInfo["type"] = _convertz.convertToTraditional(regexp.cap(5));
        updateInfo["lastUpdated"] = _convertz.convertToTraditional(regexp.cap(6));
        //updateInfo["description"] = regexp.cap(7).simplified();

        qDebug() << "SFUpdater::_getComicInfo:取得" << updateInfo;
        emit info(updateInfo);

        pos += regexp.matchedLength();
    }
}


void SFUpdateHandler::d_test()
{
    /*
      * 測試
      */
    update();
}
