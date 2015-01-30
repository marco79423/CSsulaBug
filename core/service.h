#ifndef SERVICE_H
#define SERVICE_H

#include "aservice.h"

#include "globals.h"
#include "convertz.h"

class AComicSiteHandler;
class ComicModel;
class ComicDownloader;
class FileDownloader;

class Service : public AService
{
    Q_OBJECT

public:

    explicit Service(QObject *parent = 0);
    void addComicSiteHandler(AComicSiteHandler *comicSiteHandler);

    SortFilterProxyComicModel* getComicModel();
    QStringList getChapterNames(const QString &comicKey);
    ComicModel *getDownloadComicModel();

public slots:

    void update();
    void setComicNameFilter(const QString &comicNamePattern);

    void download(const QString &comicKey);
    void download(const QString &comicKey, const QStringList &chapterNames);
    void abort(const QString &comicKey);

private slots:

     void _onUpdateFinished();

     void _onDownloadProgressChanged(const QVariantMap& downloadProgress);
     void _onDownloadFinished();

private:

    QMap<QString, AComicSiteHandler*> _comicSiteHandlers;

    ComicModel *_comicModel;
    SortFilterProxyComicModel *_proxyModel;
    ComicDownloader *_comicDownloader;

    FileDownloader *_fileDownloader;

    ConvertZ _convertz;
};

#endif // SERVICE_H
