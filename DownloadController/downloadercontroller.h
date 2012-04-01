#ifndef DOWNLOADERCONTROLLER_H
#define DOWNLOADERCONTROLLER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class DownloaderController : public QObject
{
    Q_OBJECT

public:

    explicit DownloaderController(QObject *parent = 0);
    
signals:
    

public slots:

    void download(const QString &url, const QString &dirPath);
    void done(QNetworkReply *reply);

private:

    QNetworkAccessManager *_networkAccessManager;
};

#endif // DOWNLOADERCONTROLLER_H
