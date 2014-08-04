#include "stubupdatehandler.h"

StubUpdateHandler::StubUpdateHandler(QObject *parent)
    :AUpdateHandler(parent)
{
}

void StubUpdateHandler::update()
{
    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/347639a1-530a-4550-988c-bab00a95c0fe.jpg";
        updateInfo["key"] = "JDZJ";
        updateInfo["name"] = "間諜之家";
        updateInfo["author"] = "真刈信二";
        updateInfo["type"] = "推理類";
        updateInfo["lastUpdated"] = "[011話連載中]";

        emit info(updateInfo);
    }

    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/04595fd1-746a-4ddc-9c82-05a28ba42aec.jpg";
        updateInfo["key"] = "CGX";
        updateInfo["name"] = "椿鬼";
        updateInfo["author"] = "押切蓮介";
        updateInfo["type"] = "冒險類";
        updateInfo["lastUpdated"] = "001卷[未完結]";

        emit info(updateInfo);
    }

    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/fd877ece-1ce2-45a3-9589-7f1893f23420.jpg";
        updateInfo["key"] = "SUGAR";
        updateInfo["name"] = "SUGARLESS無糖";
        updateInfo["author"] = "細川雅巳";
        updateInfo["type"] = "熱血類";
        updateInfo["lastUpdated"] = "023話[未完結]";

        emit info(updateInfo);
    }

    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/baa9dd71-d46e-4e65-96bd-26ab8efa27a3.jpg";
        updateInfo["key"] = "GWLRE";
        updateInfo["name"] = "怪物獵人Epic";
        updateInfo["author"] = "布施龍太";
        updateInfo["type"] = "冒險類";
        updateInfo["lastUpdated"] = "007話[未完結]";

        emit info(updateInfo);
    }

    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/e9e72c53-323c-410e-bf64-d3797515d4f1.jpg";
        updateInfo["key"] = "DYDF";
        updateInfo["name"] = "地獄刀鋒";
        updateInfo["author"] = "柳濟泰";
        updateInfo["type"] = "魔幻類";
        updateInfo["lastUpdated"] = "021話[未完結]";

        emit info(updateInfo);
    }

    {
        QHash<QString, QString> updateInfo;
        updateInfo["site"] = "SF";
        updateInfo["coverUrl"] = "http://mh.sfacg.com/Logo/c235c24f-40d3-4593-8387-4b3b5e5a815b.jpg";
        updateInfo["key"] = "LSWDH";
        updateInfo["name"] = "獵殺瓦達漢加";
        updateInfo["author"] = "藤澤勇希";
        updateInfo["type"] = "冒險類";
        updateInfo["lastUpdated"] = "003卷[已完結]";

        emit info(updateInfo);
    }

    emit finish();
}
