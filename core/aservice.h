#ifndef A_SERVICE_H
#define A_SERVICE_H

#include <QObject>

#include "sortfilterproxycomicmodel.h"
#include "comicmodel.h"

class AService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isCollectingStatus MEMBER _isCollectingStatus NOTIFY isCollectingStatusChangedSignal)
    Q_PROPERTY(bool isDownloadingStatus MEMBER _isDownloadingStatus NOTIFY isDownloadingStatusChangedSignal)
    Q_PROPERTY(QVariantMap downloadProgress MEMBER _downloadProgress NOTIFY isDownloadingStatusChangedSignal)

public:

    virtual SortFilterProxyComicModel* getComicModel() = 0;
    virtual ComicModel* getDownloadComicModel() = 0;

    Q_INVOKABLE virtual QStringList getChapterNames(const QString &comicKey) = 0;

signals:

    void isCollectingStatusChangedSignal();
    void collectingFinishedSignal();

    void isDownloadingStatusChangedSignal();
    void downloadProgressChangedSignal();
    void downloadFinishSignal();

public slots:

    virtual void collectComicInfos() = 0;
    virtual void setComicNameFilter(const QString &pattern) = 0;

    virtual void download(const QString &comicKey) = 0;
    virtual void download(const QString &comicKey, const QStringList &chapterNames) = 0;
    virtual void abort(const QString &comicKey) = 0;

protected:

    explicit AService(QObject *parent = 0): QObject(parent), _isCollectingStatus(false), _isDownloadingStatus(false){}

private:

    bool _isCollectingStatus;
    bool _isDownloadingStatus;
    QVariantMap _downloadProgress;
};

#endif // A_SERVICE_H
