#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <globals.h>

#include <sfcomicsitehandler.h>
#include <service.h>
#include <stub/stubservice.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);


    qRegisterMetaType<StringHash>();

    Service service(new SFComicSiteHandler);
    //StubService service;

    //顯示
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("service", &service);
    engine.rootContext()->setContextProperty("comicModel", service.getModel());

    engine.load(QUrl("qrc:ui/MainView.qml"));
    //engine.load(QUrl("qrc:ui/test.qml"));
    //*/


    return a.exec();
}
