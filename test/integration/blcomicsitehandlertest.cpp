#include "blcomicsitehandlertest.h"
#include <site/blcomicsitehandler.h>
#include <QtTest>

void BLComicSiteHandlerTest::update()
{
    BLComicSiteHandler *comicHandler = new BLComicSiteHandler(this);

    QSignalSpy comicInfoSignalSpy(comicHandler, SIGNAL(comicInfoSignal(const StringHash&)));
    QSignalSpy updateFinishSignalSpy(comicHandler, SIGNAL(updateFinishedSignal()));

    comicHandler->update();

    while(updateFinishSignalSpy.size() == 0)
        updateFinishSignalSpy.wait(1000);

    //檢查有多少部漫畫
    QCOMPARE(comicInfoSignalSpy.size(), 8660);

    //檢查抓取的漫畫是否正確
    QVariantMap comicInfo;
    for(int i = 0; i < comicInfoSignalSpy.size(); i++)
    {
        comicInfo = comicInfoSignalSpy[i].at(0).value<QVariantMap>();
        if(comicInfo["name"] == "獻給你的戀曲")
        {
            break;
        }
    }
    QCOMPARE(comicInfo["site"].toString(), QString("耽美漫畫"));
    QCOMPARE(comicInfo["coverUrl"].toString(), QString("http://imgs.hhcomic.com/comicui/24887.jpg"));
    QCOMPARE(comicInfo["key"].toString(), QString("bl24887"));
    QCOMPARE(comicInfo["name"].toString(), QString("獻給你的戀曲"));
    QCOMPARE(comicInfo["type"].toString(), QString("耽美類"));
    QCOMPARE(comicInfo["updateStatus"].toString(), QString("完結"));
}

void BLComicSiteHandlerTest::getChapters()
{
    BLComicSiteHandler *comicHandler = new BLComicSiteHandler(this);

    QList<StringPair> expectedChapters;
    expectedChapters.append(StringPair("01話","http://hh.3gmanhua.com/hu24887/177534.htm?s=10"));

    QList<StringPair> chapters = comicHandler->getChapters("bl24887");
    for(int i = 0; i < expectedChapters.size(); i++)
    {
        QCOMPARE(chapters[i].first, expectedChapters[i].first);
        QCOMPARE(chapters[i].second, expectedChapters[i].second);
    }
}

void BLComicSiteHandlerTest::getImageUrls()
{
    BLComicSiteHandler *comicHandler = new BLComicSiteHandler(this);

    QStringList expectedImageUrls;
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0001_66091.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0002_92968.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0003_70995.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0004_17073.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0005_13333.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0006_26823.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0007_73991.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0008_15069.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0009_64036.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0010_15638.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0011_15595.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0012_10472.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0013_35185.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0014_53686.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0015_74494.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0016_19789.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0017_50883.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0018_51194.JPG");
    expectedImageUrls.append("http://cdn2.3348.net:9292/dm10//ok-comic10/X/24887/act_01/99770_0019_21312.JPG");

    QStringList imageUrls = comicHandler->getImageUrls("bl24887", "http://hh.3gmanhua.com/hu24887/177534.htm?s=10");
    for(int i = 0; i < expectedImageUrls.size(); i++)
    {
        qDebug() << imageUrls[i];
        QCOMPARE(imageUrls[i], expectedImageUrls[i]);
    }
}
