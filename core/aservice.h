#ifndef A_SERVICE_H
#define A_SERVICE_H

#include <QObject>

#include "sortfilterproxycomicmodel.h"
#include "comicmodel.h"

class AService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isUpdatingStatus MEMBER _isUpdatingStatus NOTIFY isUpdatingStatusChangedSignal)
    Q_PROPERTY(bool isDownloadingStatus MEMBER _isDownloadingStatus NOTIFY isDownloadingStatusChangedSignal)
    Q_PROPERTY(QVariantMap downloadProgress MEMBER _downloadProgress NOTIFY isUpdatingStatusChangedSignal)

public:

    virtual SortFilterProxyComicModel* getComicModel() = 0;
    virtual ComicModel* getDownloadComicModel() = 0;

    Q_INVOKABLE virtual QStringList getChapterNames(const QString &comicKey) = 0;

signals:

    void isUpdatingStatusChangedSignal();
    void updateFinishedSignal();

    void isDownloadingStatusChangedSignal();
    void downloadProgressChangedSignal();
    void downloadFinishSignal();

public slots:

    virtual void update() = 0;
    virtual void setComicNameFilter(const QString &pattern) = 0;

    virtual void download(const QString &comicKey) = 0;
    virtual void download(const QString &comicKey, const QStringList &chapterNames) = 0;

protected:

    explicit AService(QObject *parent = 0): QObject(parent), _isUpdatingStatus(false), _isDownloadingStatus(false){}

private:

    bool _isUpdatingStatus;
    bool _isDownloadingStatus;
    QVariantMap _downloadProgress;
};

#endif // A_SERVICE_H
