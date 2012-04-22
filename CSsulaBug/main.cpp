#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>
#include "updatecontroller.h"

#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    UpdateController controller;
    QEventLoop loop;
    QObject::connect(&controller, SIGNAL(finish()), &loop,SLOT(quit()));
    controller.update();
    loop.exec();

    //return a.exec();
}
