#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>
#include "mainwindow.h"
#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    MainWindow w;
    w.show();
    return a.exec();
}
