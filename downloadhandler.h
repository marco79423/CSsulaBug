#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QObject>
#include <QHash>

class DownloadHandler : public QObject
{
    Q_OBJECT

public:

    explicit DownloadHandler(QObject *parent = 0):QObject(parent){}
    virtual bool isReady() const { return true;}
    
signals:

    void info(const QHash<QString, QString> &info);
    void finish();

public slots:

    virtual void download(const QString &key, const QString &dstDir){}
};

#endif // DOWNLOADHANDLER_H
