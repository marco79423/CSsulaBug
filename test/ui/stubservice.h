#ifndef STUBSERVICE_H
#define STUBSERVICE_H

#include <aservice.h>
#include <globals.h>

class ComicModel;

class StubService : public AService
{
    Q_OBJECT

public:

    explicit StubService(QObject *parent = 0);

    SortFilterProxyComicModel* getModel();
    ComicModel* getDownloadComicModel();

    QStringList getChapterNames(const QString &comicKey);

public slots:

    void update();
    void setComicNameFilter(const QString &pattern);

    void download(const QString &comicKey);
    void download(const QString &comicKey, const QStringList &chapterNames);

private slots:

    void _onUpdate();
    void _onDownload();

private:

    ComicModel *_model;
    SortFilterProxyComicModel *_proxyModel;
    ComicModel *_downloadComicModel;

    QList<QVariantMap> _comicInfos;

    QString _currentTask;
    QString _downloadProgress;
};

#endif // STUBSERVICE_H
