#ifndef ADOWNLOADSERVICE_H
#define ADOWNLOADSERVICE_H

#include <QObject>


class ADownloadService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString downloadProgress READ getDownloadProgress NOTIFY downloadProgressChanged)

public:

    virtual QString getDownloadProgress() const = 0;

signals:

    void downloadFinish();
    void downloadProgressChanged();

public slots:

    virtual void download(const QString &key) = 0;

protected:

    explicit ADownloadService(QObject *parent = 0): QObject(parent) {}

};

#endif // ADOWNLOADSERVICE_H
