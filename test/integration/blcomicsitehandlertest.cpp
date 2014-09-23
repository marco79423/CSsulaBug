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
    QCOMPARE(comicInfoSignalSpy.size(), 8563);

    //檢查抓取的漫畫是否正確
    StringHash comicInfo;
    for(int i = 0; i < comicInfoSignalSpy.size(); i++)
    {
        comicInfo = comicInfoSignalSpy[i].at(0).value<StringHash>();
        if(comicInfo["name"] == "在此尋覓你的聲音")
        {
            break;
        }
    }

    QCOMPARE(comicInfo["site"], QString("BL"));
    QCOMPARE(comicInfo["coverUrl"], QString("http://imgs.hhcomic.com/comicui/11687.jpg"));
    QCOMPARE(comicInfo["key"], QString("bl11687"));
    QCOMPARE(comicInfo["name"], QString("在此尋覓你的聲音"));
    QCOMPARE(comicInfo["type"], QString("耽美類"));
    QCOMPARE(comicInfo["lastUpdated"], QString("完結"));
}

void BLComicSiteHandlerTest::getChapters()
{
    BLComicSiteHandler *comicHandler = new BLComicSiteHandler(this);

    QList<StringPair> expectedChapters;
    expectedChapters.append(StringPair("新篇04集","http://hh.3gmanhua.com/hu11687/107886.htm?s=15"));
    expectedChapters.append(StringPair("新篇03集","http://hh.3gmanhua.com/hu11687/107885.htm?s=15"));
    expectedChapters.append(StringPair("新篇02集","http://hh.3gmanhua.com/hu11687/101705.htm?s=15"));
    expectedChapters.append(StringPair("新篇01集","http://hh.3gmanhua.com/hu11687/101704.htm?s=15"));
    expectedChapters.append(StringPair("在此尋覓你的聲音 01集","http://hh.3gmanhua.com/hu11687/97961.htm?s=15"));

    QList<StringPair> chapters = comicHandler->getChapters("bl11687");
    for(int i = 0; i < expectedChapters.size(); i++)
    {
        QCOMPARE(chapters[i].first, expectedChapters[i].first);
        QCOMPARE(chapters[i].second, expectedChapters[i].second);
    }
}

void BLComicSiteHandlerTest::getImageUrls()
{
    /*SFComicSiteHandler *comicHandler = new SFComicSiteHandler(this);

    QStringList expectedImageUrls;
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/001A_21541.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/002B_13748.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/003C_9076.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/004D_23904.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/005E_14023.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/006F_8962.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/007G_2865.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/008H_18802.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/009I_29173.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/010J_14219.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/011K_11931.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/012L_8806.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/013M_27329.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/014N_23146.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/015O_21870.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/016P_23001.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/017Q_12775.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/018R_26814.jpg");
    expectedImageUrls.append("http://pic3.sfacg.com/Pic/OnlineComic3/LIVE/004/019S_31330.jpg");

    QStringList imageUrls = comicHandler->getImageUrls("LIVE", "http://comic.sfacg.com/Utility/75/004.js");
    for(int i = 0; i < expectedImageUrls.size(); i++)
    {
        QCOMPARE(imageUrls[i], expectedImageUrls[i]);
    }*/
}
