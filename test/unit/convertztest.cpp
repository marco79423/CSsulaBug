#include "convertztest.h"

#include <QtTest>

#include <convertz.h>

void ConvertZTest::convertToTranditional()
{
    ConvertZ convertz;
    QCOMPARE(convertz.convertToTraditional("今天天气不错"), QString("今天天氣不錯"));
    QCOMPARE(convertz.convertToTraditional("杨家有女初长鸡"), QString("楊家有女初長雞"));
}
