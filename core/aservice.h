#ifndef A_SERVICE_H
#define A_SERVICE_H

#include <QObject>

#include "proxycomicmodel.h"
#include "comicmodel.h"

class AService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool collectingStatus MEMBER _collectingStatus NOTIFY collectingStatusChangedSignal)
    Q_PROPERTY(bool downloadStatus MEMBER _downloadStatus NOTIFY downloadStatusChangedSignal)
    Q_PROPERTY(QVariantMap downloadProgress MEMBER _downloadProgress NOTIFY downloadProgressChangedSignal)
    Q_PROPERTY(QString downloadPath READ getDownloadPath WRITE setDownloadPath NOTIFY downloadPathChangedSignal)

public:

    virtual ProxyComicModel* getProxyComicModel() = 0;
    virtual ComicModel* getDownloadComicModel() = 0;

    Q_INVOKABLE virtual QStringList getChapterNames(const QString &comicKey) = 0;
    Q_INVOKABLE virtual QString getDownloadPath() = 0;

signals:

    void downloadPathChangedSignal();

    void collectingStatusChangedSignal();
    void collectingFinishedSignal();

    void downloadStatusChangedSignal();
    void downloadProgressChangedSignal();
    void downloadFinishedSignal();

public slots:

    virtual void setDownloadPath(const QString &downloadPath) = 0;

    virtual void collectComicInfos() = 0;
    virtual void setComicNameFilter(const QString &pattern) = 0;

    virtual void download(const QString &comicKey) = 0;
    virtual void download(const QString &comicKey, const QStringList &chapterNames) = 0;
    virtual void abort(const QString &comicKey) = 0;

protected:

    explicit AService(QObject *parent = 0): QObject(parent), _collectingStatus(false), _downloadStatus(false){}

private:

    bool _collectingStatus;
    bool _downloadStatus;
    QVariantMap _downloadProgress;
};

#endif // A_SERVICE_H
