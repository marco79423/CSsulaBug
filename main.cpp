#include <QApplication>
#include <QTextCodec>
#include <QtDeclarative>
#include "core.h"
#include "comicmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //*
    //CSsulaBug 的核心
    Core core;

    //顯示
    QDeclarativeView view;
    view.rootContext()->setContextProperty("core", &core);
    view.rootContext()->setContextProperty("comicModel", core.model());
    view.setSource(QUrl("qrc:ui/MainView.qml"));
    view.show();
    //*/

    /*
    ComicModel tester;
    tester.d_test();
    //*/

    return a.exec();
}
