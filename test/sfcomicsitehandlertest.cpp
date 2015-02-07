#include "sfcomicsitehandlertest.h"
#include "testglobals.h"

#include <site/sfcomicsitehandler.h>
#include <QtTest>

void SFComicSiteHandlerTest::initTestCase()
{
    qInstallMessageHandler(noMessageOutput);
}

void SFComicSiteHandlerTest::collectComicInfos()
{
    SFComicSiteHandler *comicHandler = new SFComicSiteHandler(this);

    QSignalSpy comicInfoSignalSpy(comicHandler, SIGNAL(comicInfoSignal(const QVariantMap&)));
    QSignalSpy collectingFinishSignalSpy(comicHandler, SIGNAL(collectingFinishSignal()));

    comicHandler->collectComicInfos();

    while(collectingFinishSignalSpy.size() == 0)
        collectingFinishSignalSpy.wait(1000);

    //檢查有多少部漫畫
    //QCOMPARE(comicInfoSignalSpy.size(), 1592);

    //檢查抓取的漫畫是否正確
    QVariantMap comicInfo;
    for(int i = 0; i < comicInfoSignalSpy.size(); i++)
    {
        comicInfo = comicInfoSignalSpy[i].at(0).value<QVariantMap>();
        if(comicInfo["name"].toString() == "LIVE")
        {
            break;
        }
    }

    QCOMPARE(comicInfo["site"].toString(), QString("SF 互動傳媒網"));
    QCOMPARE(comicInfo["coverUrl"].toString(), QString("http://mh.sfacg.com/Logo/LIVE.jpg"));
    QCOMPARE(comicInfo["key"].toString(), QString("LIVE"));
    QCOMPARE(comicInfo["name"].toString(), QString("LIVE"));
    QCOMPARE(comicInfo["author"].toString(), QString("梅澤春人"));
    QCOMPARE(comicInfo["type"].toString(), QString("熱血類"));
    QCOMPARE(comicInfo["updateStatus"].toString(), QString("010話[已完結]"));
}

void SFComicSiteHandlerTest::getChapters()
{
    SFComicSiteHandler *comicHandler = new SFComicSiteHandler(this);

    QList<StringPair> expectedChapters;
    expectedChapters.append(StringPair("010話","http://comic.sfacg.com/Utility/75/010.js"));
    expectedChapters.append(StringPair("009話","http://comic.sfacg.com/Utility/75/009.js"));
    expectedChapters.append(StringPair("008話","http://comic.sfacg.com/Utility/75/008.js"));
    expectedChapters.append(StringPair("007話","http://comic.sfacg.com/Utility/75/007.js"));
    expectedChapters.append(StringPair("006話","http://comic.sfacg.com/Utility/75/006.js"));
    expectedChapters.append(StringPair("005話","http://comic.sfacg.com/Utility/75/005.js"));
    expectedChapters.append(StringPair("004話","http://comic.sfacg.com/Utility/75/004.js"));
    expectedChapters.append(StringPair("003話","http://comic.sfacg.com/Utility/75/003.js"));
    expectedChapters.append(StringPair("002話","http://comic.sfacg.com/Utility/75/002.js"));
    expectedChapters.append(StringPair("001話","http://comic.sfacg.com/Utility/75/001.js"));

    QList<StringPair> chapters = comicHandler->getChapters("LIVE");
    for(int i = 0; i < expectedChapters.size(); i++)
    {
        QCOMPARE(chapters[i].first, expectedChapters[i].first);
        QCOMPARE(chapters[i].second, expectedChapters[i].second);
    }
}

void SFComicSiteHandlerTest::getImageUrls()
{
    SFComicSiteHandler *comicHandler = new SFComicSiteHandler(this);

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
    }
}
