#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <sfupdatehandler.h>
#include <sfdownloadhandler.h>
#include <core.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    //*
    //CSsulaBug 的核心
    AUpdateHandler *updateHandler = new SFUpdateHandler();
    ADownloadHandler *downloadHandler = new SFDownloadHandler();
    Core core(updateHandler, downloadHandler);

    //顯示
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("core", &core);
    engine.rootContext()->setContextProperty("comicModel", core.getModel());
    engine.load(QUrl("qrc:ui/MainView.qml"));

    return a.exec();
}
