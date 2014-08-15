#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QObject>

#include "globals.h"

class AComicSiteHandler;
class FileDownloader;

class DownloadHandler : public QObject
{
    Q_OBJECT

public:

    explicit DownloadHandler(AComicSiteHandler *comicSiteHandler, QObject *parent = 0);

signals:

    void downloadInfoSignal(const StringHash &info);
    void downloadFinishedSignal();

public slots:

    void download(const QString &comicKey, const QString &dstDir);
    void download(const QString &comicKey, const StringPair &chapter, const QString &dstDir);

private:

    AComicSiteHandler *_comicSiteHandler;
    FileDownloader *_fileDownloader;
};

#endif // DOWNLOADHANDLER_H
