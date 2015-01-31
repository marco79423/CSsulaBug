#include "filedownloadertest.h"

#include <filedownloader.h>
#include <QtTest>


void FileDownloaderTest::download()
{
    FileDownloader *fileDownloader = new FileDownloader(this);

    QSignalSpy downloadInfoSignalSpy(fileDownloader, SIGNAL(downloadInfoSignal(QVariantMap)));
    QSignalSpy finishSpy(fileDownloader, SIGNAL(finishSignal()));

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    QString path = "testdir/marco.jpg";

    FileDownloader::Task task;
    task[url] = path;
    fileDownloader->download(task);

    while(downloadInfoSignalSpy.size() == 0)
        downloadInfoSignalSpy.wait(100);

    while(finishSpy.size() == 0)
        finishSpy.wait(100);

    QList<QVariant> args = downloadInfoSignalSpy.takeFirst();
    QVariantMap downloadInfo = args.at(0).value<QVariantMap>();

    QCOMPARE(downloadInfo["url"].toString(), url);
    QCOMPARE(downloadInfo["path"].toString(), path);
    QCOMPARE(downloadInfo["ratio"].toFloat(), float(1));

    QFile file1(":/images/marco.jpg");
    QVERIFY(file1.open(QFile::ReadOnly));

    QFile file2(":/images/marco.jpg");
    QVERIFY(file2.open(QFile::ReadOnly));

    QCOMPARE(file1.readAll(), file2.readAll());
}

void FileDownloaderTest::abort()
{
    FileDownloader *fileDownloader = new FileDownloader(this);

    QSignalSpy downloadInfoSignalSpy(fileDownloader, SIGNAL(downloadInfoSignal(QVariantMap)));
    QSignalSpy finishSpy(fileDownloader, SIGNAL(finishSignal()));

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    QString path = "testdir/marco.jpg";

    FileDownloader::Task task;
    task[url] = path;
    fileDownloader->download(task);
    fileDownloader->abort();

    while(finishSpy.size() == 0)
        finishSpy.wait(100);

    QVERIFY(downloadInfoSignalSpy.isEmpty());
}

void FileDownloaderTest::cleanupTestCase()
{
    if(QFileInfo::exists("testdir"))
    {
        QDir dir("testdir");
        dir.removeRecursively();
    }
}
