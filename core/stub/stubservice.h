#ifndef STUBSERVICE_H
#define STUBSERVICE_H

#include "../aservice.h"

#include "../globals.h"

class ComicModel;

class StubService : public AService
{
    Q_OBJECT

public:

    explicit StubService(QObject *parent = 0);

    QSortFilterProxyModel* getModel();

    QStringList getChapters(const QString &comicKey);

    bool isUpdating();
    bool isDownloading();
    QString getDownloadProgress();

public slots:

    void update();
    void setFilter(const QString &pattern);

    void download(const QString &comicKey);
    void download(const QString &comicKey, const QStringList &chapterNames);

private slots:

    void _onUpdate();
    void _onDownload();

private:

    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;

    QList<StringHash> _comicInfos;

    bool _isUpdating;
    bool _isDownloading;

    QString _currentTask;
    QString _downloadProgress;
};

#endif // STUBSERVICE_H
