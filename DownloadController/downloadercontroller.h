#ifndef DOWNLOADERCONTROLLER_H
#define DOWNLOADERCONTROLLER_H

#include <QObject>
#include <QHash>
#include <QStringList>

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

private slots:

    void listDownloadList();
    void get(const QString &url);
    void onReply(QNetworkReply *reply);

private:

    QNetworkAccessManager *_networkAccessManager;
    SFDownloadPreparer *_downloadPreparer;

    QString _comicName;
    QString _dirPath;
    QHash<QString, QString> _downloadHash;
};

#endif // DOWNLOADERCONTROLLER_H
