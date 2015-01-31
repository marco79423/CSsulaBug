#ifndef COMICDOWNLOADERTEST_H
#define COMICDOWNLOADERTEST_H

#include <QObject>

class ComicDownloaderTest : public QObject
{
    Q_OBJECT

private slots:

    void download();
    void abort();

};

#endif // COMICDOWNLOADERTEST_H
