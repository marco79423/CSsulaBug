#include "fakedata.h"
#include <globals.h>

FakeData::FakeData()
{
    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/347639a1-530a-4550-988c-bab00a95c0fe.jpg";
        comicInfo["key"] = "JDZJ";
        comicInfo["name"] = "間諜之家";
        //comicInfo["author"] = "真刈信二";
        comicInfo["type"] = "推理類";
        comicInfo["updateStatus"] = "[011話連載中]";  

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/04595fd1-746a-4ddc-9c82-05a28ba42aec.jpg";
        comicInfo["key"] = "CGX";
        comicInfo["name"] = "椿鬼";
        comicInfo["author"] = "押切蓮介";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "001卷[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/fd877ece-1ce2-45a3-9589-7f1893f23420.jpg";
        comicInfo["key"] = "SUGAR";
        comicInfo["name"] = "SUGARLESS無糖";
        comicInfo["author"] = "細川雅巳";
        comicInfo["type"] = "熱血類";
        comicInfo["updateStatus"] = "023話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/baa9dd71-d46e-4e65-96bd-26ab8efa27a3.jpg";
        comicInfo["key"] = "GWLRE";
        comicInfo["name"] = "怪物獵人Epic";
        comicInfo["author"] = "布施龍太";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "007話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/e9e72c53-323c-410e-bf64-d3797515d4f1.jpg";
        comicInfo["key"] = "DYDF";
        comicInfo["name"] = "地獄刀鋒";
        comicInfo["author"] = "柳濟泰";
        comicInfo["type"] = "魔幻類";
        comicInfo["updateStatus"] = "021話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/167a1629-5581-480d-aebc-2474323a48a6.jpg";
        comicInfo["key"] = "WDQCL";
        comicInfo["name"] = "我的青春戀愛喜劇果然有問題";
        comicInfo["author"] = "佳月玲茅";
        comicInfo["type"] = "校園類";
        comicInfo["updateStatus"] = "022話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        QVariantMap comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/c235c24f-40d3-4593-8387-4b3b5e5a815b.jpg";
        comicInfo["key"] = "LSWDH";
        comicInfo["name"] = "獵殺瓦達漢加";
        comicInfo["author"] = "藤澤勇希";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "003卷[已完結]";

        _comicInfos.append(comicInfo);
    }
}

QVariantMap FakeData::getComicInfo(const int &index, const bool &withoutChapters)
{
    QVariantMap comicInfo = _comicInfos[index];
    if(!withoutChapters)
    {
        comicInfo["chapters"].setValue(getChapters(comicInfo["key"].toString()));
    }
    return comicInfo;
}

int FakeData::getComicInfoCount()
{
    return _comicInfos.size();
}


QStringList FakeData::getImageUrls(const QString &comicKey, const QString &chapterKey)
{
    QStringList imageUrls;
    for(int i = 0; i < 5; i++)
    {
        imageUrls << QString("image%1%2%3").arg(comicKey).arg(chapterKey).arg(i);
    }
    return imageUrls;
}

QList<StringPair> FakeData::getChapters(const QString &comicKey)
{
    QList<StringPair> chapters;
    for(int i=0; i < 10; i++)
    {
        QString chapterName = QString("第%1話").arg(i, 3, 10, QChar('0'));
        QString chapterKey = QString("chapterKey%1%2").arg(comicKey).arg(i);
        chapters.append(StringPair(chapterName, chapterKey));
    }
    return chapters;
}
