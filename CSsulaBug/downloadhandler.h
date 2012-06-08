#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QObject>
#include <QHash>

class DownloadHandler : public QObject
{
    Q_OBJECT

public:

    explicit DownloadHandler(QObject *parent = 0);
    
signals:

    void downloadInfo(const QHash<QString, QString> &info);
    void downloadFinish();

public slots:

    virtual void download(const QString &name, const QString &dstDir){}
};

#endif // DOWNLOADHANDLER_H
