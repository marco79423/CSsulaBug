#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>
#include "mainwindow.h"
#include <QEventLoop>
#include "networkaccessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    //MainWindow w;
    //w.show();

    NetworkAccessor n;
    n.get(0, "http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe");
    n.get(1, QStringList() << "http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe"
              << "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe");
    return a.exec();
}
