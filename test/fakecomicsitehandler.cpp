#include "fakecomicsitehandler.h"
#include <QTimer>

FakeComicSiteHandler::FakeComicSiteHandler(QObject *parent)
    :AComicSiteHandler(parent)
{

}


QString FakeComicSiteHandler::getComicSiteName() const
{
    return "FakeSite";
}

QString FakeComicSiteHandler::getReferer() const
{
    return "fakeReferer";
}

void FakeComicSiteHandler::collectComicInfos()
{
    for(int i=0; i< _fakeData.getComicInfoCount(); i++)
    {
        QTimer::singleShot(i * 500, this, SLOT(onComicInfoSignal(comicInfo)));
    }
}

void FakeComicSiteHandler::onComicInfoSignal()
{
    static int i=0;
    emit comicInfoSignal(_fakeData.getComicInfo(i));
    if(i == _fakeData.getComicInfoCount() - 1)
    {
        emit collectingFinishedSignal();
        i=0;
    }

    i+=1;
}

QStringList FakeComicSiteHandler::getImageUrls(const QString &comicKey, const QString &chapterKey)
{
    return _fakeData.getImageUrls(comicKey, chapterKey);
}

QList<StringPair> FakeComicSiteHandler::getChapters(const QString &comicKey)
{
    return _fakeData.getChapters(comicKey);
}
