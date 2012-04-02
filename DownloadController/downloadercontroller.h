#ifndef DOWNLOADERCONTROLLER_H
#define DOWNLOADERCONTROLLER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class SFDownloadPreparer;

class DownloaderController
        :public QObject
{
    Q_OBJECT

public:

    explicit DownloaderController(QObject *parent = 0);
    
signals:
    
    void finish();

public slots:

    void download(const QString &key, const QString &dirPath);
    void onReply(QNetworkReply *reply);

private:

    QNetworkAccessManager *_networkAccessManager;
    SFDownloadPreparer *_downloadPreparer;
};

#endif // DOWNLOADERCONTROLLER_H
