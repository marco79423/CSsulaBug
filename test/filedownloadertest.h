#ifndef FILEDOWNLOADERTEST_H
#define FILEDOWNLOADERTEST_H

#include <QObject>

class FileDownloaderTest : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase();

    void download();
    void abort();

    void cleanupTestCase();
};

#endif // FILEDOWNLOADERTEST_H
