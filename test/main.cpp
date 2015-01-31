#include <QCoreApplication>
#include <QTest>

#include "testglobals.h"

#include "convertztest.h"
#include "networkaccessortest.h"
#include "filedownloadertest.h"

#include "sfcomicsitehandlertest.h"
#include "blcomicsitehandlertest.h"

#include "comicmodeltest.h"
#include "sortfilterproxycomicmodeltest.h"
#include "comicdownloadertest.h"
#include "servicetest.h"

void noMessageOutput(QtMsgType, const QMessageLogContext&, const QString&){}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);
    Q_INIT_RESOURCE(test_resource);

    int ret = 0;

    //Utilities
    ConvertZTest convertZTest;
    ret += QTest::qExec(&convertZTest, argc, argv);

    NetworkAccessorTest networkAccessorTest;
    ret += QTest::qExec(&networkAccessorTest, argc, argv);

    FileDownloaderTest fileDownloaderTest;
    ret += QTest::qExec(&fileDownloaderTest, argc, argv);

    //ComicSites
    SFComicSiteHandlerTest sfComicSiteHandlerTest;
    ret += QTest::qExec(&sfComicSiteHandlerTest, argc, argv);

    BLComicSiteHandlerTest blComicSiteHandlerTest;
    ret += QTest::qExec(&blComicSiteHandlerTest, argc, argv);

    //Core
    //ComicModelTest comicModelTest;
    //ret += QTest::qExec(&comicModelTest, argc, argv);

    //SortFilterProxyComicModelTest sortFilterProxyComicModelTest;
    //ret += QTest::qExec(&sortFilterProxyComicModelTest, argc, argv);

    //ComicDownloaderTest comicDownloaderTest;
    //ret += QTest::qExec(&comicDownloaderTest, argc, argv);

    //ServiceTest serviceTest;
    //ret += QTest::qExec(&serviceTest, argc, argv);

    //UI
    //not implemented

    return ret;
}

