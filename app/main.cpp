#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <sfupdatehandler.h>
#include <sfdownloadhandler.h>
#include <comicinfoservice.h>
#include <downloadservice.h>

#include <stub/stubupdatehandler.h>
#include <stub/stubdownloadhandler.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);


    qRegisterMetaType<AUpdateHandler::ComicInfo>();

    //*
    //CSsulaBug 的核心
    ComicInfoService comicInfoService(new SFUpdateHandler);
    //ComicInfoService comicInfoService(new StubUpdateHandler);

    //DownloadService downloadService(new SFDownloadHandler);
    DownloadService downloadService(new StubDownloadHandler);

    //顯示
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("comicInfoService", &comicInfoService);
    engine.rootContext()->setContextProperty("comicModel", comicInfoService.getModel());
    engine.rootContext()->setContextProperty("downloadService", &downloadService);
    engine.load(QUrl("qrc:ui/MainView.qml"));

    return a.exec();
}
