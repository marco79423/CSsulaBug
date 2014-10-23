#ifndef SERVICE_H
#define SERVICE_H

#include "aservice.h"

#include "globals.h"
#include "convertz.h"

class AComicSiteHandler;
class ComicModel;
class FileDownloader;

class Service : public AService
{
    Q_OBJECT

public:

    explicit Service(QObject *parent = 0);
    void addComicSiteHandler(AComicSiteHandler *comicSiteHandler);

    SortFilterProxyComicModel* getModel();
    QStringList getChapterNames(const QString &comicKey);

public slots:

    void update();
    void setComicTypeFilter(const QString &comicTypePattern);
    void setComicNameFilter(const QString &comicNamePattern);

    void download(const QString &comicKey);
    void download(const QString &comicKey, const QStringList &chapterNames);

private slots:

     void _onUpdateFinished();
     void _onGettingDownloadProgress(const int &id, const StringHash &info);
     void _onTaskFinish(const int &id);

private:

    QMap<QString, AComicSiteHandler*> _comicSiteHandlers;

    ComicModel *_model;
    SortFilterProxyComicModel *_proxyModel;

    QHash<QString, QList<StringPair> > _chapterInfo;

    QList<int> _currentTaskIDs;
    int _currentTaskSize;

    FileDownloader *_fileDownloader;

    ConvertZ _convertz;
};

#endif // SERVICE_H
