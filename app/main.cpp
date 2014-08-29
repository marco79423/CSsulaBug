#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <globals.h>
#include <sfcomicsitehandler.h>
#include <service.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    qRegisterMetaType<StringHash>();

    Service service(new SFComicSiteHandler);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("service", &service);
    engine.rootContext()->setContextProperty("comicModel", service.getModel());
    engine.load(QUrl("qrc:ui/MainView.qml"));

    return a.exec();
}
