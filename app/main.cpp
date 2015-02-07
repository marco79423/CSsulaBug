#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>

#include <globals.h>
#include <site/sfcomicsitehandler.h>
#include <site/blcomicsitehandler.h>

#include <service.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QFont font("新細明體");
    font.setPixelSize(12);
    a.setFont(font);

    Q_INIT_RESOURCE(core_resource);

    Service service;
    service.addComicSiteHandler(new SFComicSiteHandler);
    service.addComicSiteHandler(new BLComicSiteHandler);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("service", &service);
    engine.rootContext()->setContextProperty("comicModel", service.getComicModel());
    engine.rootContext()->setContextProperty("downloadComicModel", service.getDownloadComicModel());
    engine.load(QUrl("qrc:ui/MainView.qml"));

    return a.exec();
}
