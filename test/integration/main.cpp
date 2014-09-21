#include <QCoreApplication>
#include <QDebug>
#include <QTest>

#include "filesavertest.h"
#include "networkaccessortest.h"
#include "sfcomicsitehandlertest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    int ret = 0;

    FileSaverTest fileSaverTest;
    ret += QTest::qExec(&fileSaverTest, argc, argv);

    NetworkAccessorTest networkAccessorTest;
    ret += QTest::qExec(&networkAccessorTest, argc, argv);

    SFComicSiteHandlerTest sfComicSiteHandlerTest;
    ret += QTest::qExec(&sfComicSiteHandlerTest, argc, argv);

    return ret;
}
