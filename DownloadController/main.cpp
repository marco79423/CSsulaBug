#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QEventLoop>
#include "downloadercontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    DownloaderController controller;
    controller.download("DJWY", "C:/Users/Marco/Desktop");
    QEventLoop loop;
    QObject::connect(&controller, SIGNAL(finish()), &loop, SLOT(quit()));
    loop.exec();
}
