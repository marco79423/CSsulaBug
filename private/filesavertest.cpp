#include "filesavertest.h"

#include <QtTest>
#include <QList>
#include <QByteArray>
#include <QFileInfo>

#include <filesaver.h>

void FileSaverTest::initTestCase()
{
    
}

void FileSaverTest::saveFile()
{
    AFileSaver *fileSaver = new FileSaver(this);
    QSignalSpy spy(fileSaver, SIGNAL(finish(const int&, const AFileSaver::SaverStatus&)));

    QByteArray array("今天天氣不錯");
    QString filePath = "test/a";
    const int id = fileSaver->saveFile(array, filePath);

    QVERIFY(spy.wait(1000));

    QList<QVariant> args = spy.takeFirst();
    QVERIFY(args.at(0).toInt() == id);
    QVERIFY((AFileSaver::SaverStatus)args.at(1).toInt() ==  AFileSaver::SaverStatus::Success);

    QFileInfo fileInfo(filePath);
    QVERIFY(fileInfo.exists());

    QDir dir = fileInfo.absoluteDir();
    QVERIFY(dir.exists());

    QFile file(filePath);
    QVERIFY(file.open(QFile::ReadOnly));
    QCOMPARE(file.readAll(), array);
    file.close();
}

void FileSaverTest::cleanupTestCase()
{

}
