#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include "core.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    //*
    //CSsulaBug 的核心
    Core core;

    //顯示
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("core", &core);
    engine.rootContext()->setContextProperty("comicModel", core.getModel());
    engine.load(QUrl("qrc:ui/MainView.qml"));

    return a.exec();
}
