#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <globals.h>

#include <sfupdatehandler.h>
#include <sfdownloadhandler.h>
#include <comicinfoservice.h>
#include <downloadservice.h>

#include <stub/stubupdatehandler.h>
#include <stub/stubdownloadhandler.h>

#include <QDebug>
#include <sfcomicsitehandler.h>
#include <service.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);


    qRegisterMetaType<StringHash>();

    /*
    SFComicSiteHandler handler;
    QList<StringPair> list = handler.getChapters("GWLRE");
    qDebug() << list;

    QStringList urls = handler.getImageUrls("http://comic.sfacg.com/Utility/1280/005.js");
    qDebug() << urls;

    handler.updateComicInfos();
    //*/

    //*
    //CSsulaBug 的核心
    //ComicInfoService comicInfoService(new SFComicSiteHandler);
    //ComicInfoService comicInfoService(new StubUpdateHandler);

    //DownloadService downloadService(new SFComicSiteHandler);
    //DownloadService downloadService(new StubDownloadHandler);[

    Service service(new SFComicSiteHandler);

    //顯示
    QQmlApplicationEngine engine;

    //engine.rootContext()->setContextProperty("comicInfoService", &comicInfoService);
    //engine.rootContext()->setContextProperty("comicModel", comicInfoService.getModel());
    //engine.rootContext()->setContextProperty("downloadService", &downloadService);

    engine.rootContext()->setContextProperty("service", &service);
    engine.rootContext()->setContextProperty("comicModel", service.getModel());

    engine.load(QUrl("qrc:ui/MainView.qml"));
    //*/


    return a.exec();
}
