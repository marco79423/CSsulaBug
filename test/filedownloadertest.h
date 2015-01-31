#ifndef FILEDOWNLOADERTEST_H
#define FILEDOWNLOADERTEST_H

#include <QObject>

class FileDownloaderTest : public QObject
{
    Q_OBJECT

private slots:

    void download();
    void abort();

};

#endif // FILEDOWNLOADERTEST_H
