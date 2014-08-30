#include "filesavertest.h"

#include <QtTest>
#include <QList>
#include <QByteArray>
#include <QFileInfo>

#include <filesaver.h>

void FileSaverTest::initTestCase()
{
    _testcases["a"] = QByteArray("今天天氣不錯");
    _testcases["testdir/b"] = QByteArray("楊家有女初長雞");
    _testcases["testdir/c/d"] = QByteArray("哈哈");
}

void FileSaverTest::saveFile()
{
    AFileSaver *fileSaver = new FileSaver(this);
    foreach(QString filePath, _testcases.keys())
    {
        AFileSaver::SaverStatus status = fileSaver->saveFile(_testcases[filePath], filePath);

        QCOMPARE(status, AFileSaver::Success);
        QFileInfo fileInfo(filePath);
        QVERIFY(fileInfo.exists());

        QDir dir = fileInfo.absoluteDir();
        QVERIFY(dir.exists());

        QFile file(filePath);
        QVERIFY(file.open(QFile::ReadOnly));
        QCOMPARE(file.readAll(), _testcases[filePath]);
        file.close();
    }
}

void FileSaverTest::cleanupTestCase()
{
    if(QFileInfo::exists("a"))
    {
        QFile::remove("a");
    }

    if(QFileInfo::exists("testdir"))
    {
        QDir dir("testdir");
        dir.removeRecursively();
    }
}
