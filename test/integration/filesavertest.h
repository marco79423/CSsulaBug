#ifndef FILESAVERTEST_H
#define FILESAVERTEST_H

#include <QObject>
#include <QMap>

class FileSaverTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void saveFile();
    void cleanupTestCase();

private:

    QMap<QString, QByteArray> _testcases;
};

#endif // FILESAVERTEST_H
