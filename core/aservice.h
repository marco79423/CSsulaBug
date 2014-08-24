#ifndef A_SERVICE_H
#define A_SERVICE_H

#include <QObject>
#include <QSortFilterProxyModel>

class AService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool updating READ isUpdating NOTIFY isUpdatingChangedSignal)
    Q_PROPERTY(bool downloading READ isDownloading NOTIFY isDownloadingChangedSignal)
    Q_PROPERTY(QString downloadProgress READ getDownloadProgress NOTIFY downloadProgressChangedSignal)

public:

    virtual QSortFilterProxyModel* getModel() = 0;

    Q_INVOKABLE virtual QStringList getChapterNames(const QString &comicKey) = 0;

    virtual bool isUpdating() = 0;
    virtual bool isDownloading() = 0;
    virtual QString getDownloadProgress() = 0;

signals:

    void isUpdatingChangedSignal();
    void updateFinishedSignal();

    void isDownloadingChangedSignal();
    void downloadProgressChangedSignal();
    void downloadFinishSignal();

public slots:

    virtual void update() = 0;
    virtual void setFilter(const QString &pattern) = 0;

    virtual void download(const QString &comicKey) = 0;
    virtual void download(const QString &comicKey, const QStringList &chapterNames) = 0;

protected:

    explicit AService(QObject *parent = 0): QObject(parent){}

};

#endif // A_SERVICE_H
