#include "sfupdatehandler.h"
#include "networkaccessor.h"

#include <QNetworkReply>
#include <QDebug>

SFUpdateHandler::SFUpdateHandler(QObject *parent) :
    UpdateHandler(parent), _currentState(NothingDoing)
{
    _networkAccessor = new NetworkAccessor(this);
    _setConnection();
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
    switch(_currentState)
    {
    case NothingDoing:
        qDebug() << "SFUpdateHandler:update:開始更新";
        _startProcess(ALLPageUrlListGetting);
        break;
    default:
        qDebug() << "SFUpdateHandler:update:現在狀態還不能更新";
        break;
    }
}

void SFUpdateHandler::_onAccessorReply(const int &id, QNetworkReply *networkReply)
{
    switch(_currentState)
    {
    case ALLPageUrlListGetting:
        _getPageUrl(networkReply->readAll());
        qDebug() << "SFUpdateHandler:_onAccessorReply:取得 allPageUrlList";
        break;
    case ComicInfoGetting:
        _getComicInfo(networkReply->readAll());
        qDebug() << "SFUpdateHandler:_onAccessorReply:取得 " << networkReply->url() << "的資訊";
        break;
    default:
        qCritical() << "SFUpdateHandler:_onAccessorReply:錯誤的狀態" << _currentState;
        break;
    }
}

void SFUpdateHandler::_onAccessorFinish(const int &id)
{
    switch(_currentState)
    {
    case ALLPageUrlListGetting:
        qDebug() << "SFUpdateHandler:_onAccessorFinish:進入 ComicInfoGetting 階段";
        _startProcess(ComicInfoGetting);
        break;
    case ComicInfoGetting:
        qDebug() << "下載完成";
        emit finish();
        break;
    default:
        break;
    }
}

void SFUpdateHandler::_setConnection()
{
    connect(_networkAccessor, SIGNAL(reply(const int&,QNetworkReply*)),
            SLOT(_onAccessorReply(const int&,QNetworkReply*)));
    connect(_networkAccessor, SIGNAL(finish(const int&)),
            SLOT(_onAccessorFinish(const int&)));
}

void SFUpdateHandler::_startProcess(const State &state)
{
    qDebug() << "SFUpdateHandler:_startProcess:開始執行 " << state << "狀態";
    switch(state)
    {
    case ALLPageUrlListGetting:
        _currentState = ALLPageUrlListGetting;
        _networkAccessor->get(0, "http://comic.sfacg.com/Catalog/");
        break;
    case ComicInfoGetting:
        _currentState = ComicInfoGetting;
        _networkAccessor->get(1, _allPageUrlList);
        break;
    default:
        qCritical() << "SFUpdateHandler:_startProcess:錯誤的狀態 " << state;
    }
}

void SFUpdateHandler::_getPageUrl(const QString &html)
{
    int maxPageNumber = 0;

    QRegExp pageNumExp("http://comic.sfacg.com/Catalog/"
                       "Default.aspx\\?PageIndex=(\\d+)");

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

    _allPageUrlList.clear();
    for(int i = 1; i <= maxPageNumber; i++)
    {
        _allPageUrlList.append("http://comic.sfacg.com/Catalog/Default.aspx?"
                       "PageIndex=" + QString::number(i));
    }
}

void SFUpdateHandler::_getComicInfo(const QString &html)
{
    QRegExp regexp("<img src=\"([^\"]+)\"" //cover
                   "[^>]+></a></li>\\s+<li><strong class=\""
                   "F14PX\"><a href=\"/HTML/([^/]+)" //keyName
                   "[^>]+>([^<]+)" //name
                   "[^1]+1\">([^<]+)" //comicAuthor
                   "[^\\]]+[^>]+>([^<]+)" //comicType
                   "</a> /([^/]+)+/" //lastUpdated
                   " \\d+<br />([^<]+)" //description
                   );

    int pos = 0;
    while ((pos = regexp.indexIn(html, pos)) != -1)
    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = regexp.cap(1);
        updateInfo["key"] = regexp.cap(2);
        updateInfo["name"] = regexp.cap(3);
        updateInfo["author"] = regexp.cap(4);
        updateInfo["type"] = regexp.cap(5);
        updateInfo["lastUpdated"] = regexp.cap(6);
        updateInfo["description"] = regexp.cap(7).simplified();

        qDebug() << "SFUpdater::_getComicInfo:取得" << updateInfo;
        emit info(updateInfo);

        pos += regexp.matchedLength();
    }
}
