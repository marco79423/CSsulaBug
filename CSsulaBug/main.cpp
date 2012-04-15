#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>

#include "sfupdater.h"
#include "comicdatabase.h"
#include "sfcoverupdater.h"

#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    ComicDatabase db;

    /*SFUpdater updater;
    QEventLoop loop;
    QObject::connect(&updater, SIGNAL(finish()), &loop,SLOT(quit()));
    updater.update();
    loop.exec();

    SFCoverUpdater coverUpdater;
    QObject::connect(&coverUpdater, SIGNAL(finish()), &loop,SLOT(quit()));
    coverUpdater.update(updater.getComicList());
    loop.exec();*/

    //return a.exec();
}
