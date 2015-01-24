#include <gmock/gmock.h>
#include <convertz.h>

TEST(convertz, convertToTraditional)
{
    ConvertZ convertz;
    EXPECT_EQ(QString("今天天氣不錯"), convertz.convertToTraditional("今天天气不错"));
    EXPECT_EQ(QString("楊家有女初長雞"), convertz.convertToTraditional("杨家有女初长鸡"));
}
