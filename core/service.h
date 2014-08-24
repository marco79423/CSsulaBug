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

    explicit Service(AComicSiteHandler *comicSiteHandler, QObject *parent = 0);

    QSortFilterProxyModel* getModel();
    QStringList getChapterNames(const QString &comicKey);

    virtual bool isUpdating();
    virtual bool isDownloading();
    virtual QString getDownloadProgress();

public slots:

    void update();
    void setFilter(const QString &pattern);

    void download(const QString &comicKey);
    void download(const QString &comicKey, const QStringList &chapterNames);

private slots:

     void _onUpdateFinished();
     void _onGettingDownloadProgress(const int &id, const StringHash &info);
     void _onTaskFinish(const int &id, const bool &error);

private:

    AComicSiteHandler *_comicSiteHandler;

    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;

    QHash<QString, QList<StringPair> > _chapterInfo;

    bool _isUpdating;
    bool _isDownloading;
    QString _downloadProgress;

    QList<int> _currentTaskIDs;
    int _currentTaskSize;

    FileDownloader *_fileDownloader;

    ConvertZ _convertz;
};

#endif // SERVICE_H
