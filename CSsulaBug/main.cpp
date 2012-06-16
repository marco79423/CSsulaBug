#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>
#include "mainwindow.h"
#include <QEventLoop>
#include "downloader.h"
#include "networkaccessor.h"
#include "sfupdatehandler.h"
#include "sfdownloadhandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    //MainWindow w;
    //w.show();

    QString url1 = "http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe";
    QString url2 = "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe";

    /* for NetworkAccessor
    NetworkAccessor accessor;
    accessor.get(0, url1);
    accessor.get(1, QStringList() << url1 << url2);
    //*/

    /* for Downloader
    Downloader::Task task1;
    task1.urlList.append(url1);
    task1.pathList[url1] = "1a.exe";

    Downloader::Task task2;
    task2.urlList << url1 << url2;
    task2.pathList[url1] = "2a.exe";
    task2.pathList[url2] = "2b.exe";

    Downloader d;
    d.download(task1);
    d.download(task2);
    //*/

    /* for SFUpdateHandler
    SFUpdateHandler handler;
    handler.update();
    //*/

    //* for SFDownloadHandler
    SFDownloadHandler handler;
    handler.download("FSJII", "漫畫");
    //*/

    return a.exec();
}
