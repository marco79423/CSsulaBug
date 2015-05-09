#include "mainwindow.h"
#include <QApplication>

#include <service.h>
#include <comicsitehandler/sfcomicsitehandler.h>
#include <comicsitehandler/blcomicsitehandler.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    Service service;
    service.addComicSiteHandler(new SFComicSiteHandler);
    service.addComicSiteHandler(new BLComicSiteHandler);

    MainWindow w(&service);
    w.show();

    return a.exec();
}
