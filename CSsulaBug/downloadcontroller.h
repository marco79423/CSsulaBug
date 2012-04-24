#ifndef DOWNLOADCONTROLLER_H
#define DOWNLOADCONTROLLER_H

#include <QObject>
#include <QHash>
#include <QStringList>

class NetworkAccessor;
class SFDownloadPreparer;

class DownloadController
        :public QObject
{
    Q_OBJECT

public:

    explicit DownloadController(QObject *parent = 0);
    
signals:
    
    void finish();

public slots:

    void download(const QString &key, const QString &name);

private slots:

    void downloadImages();

    void onOneReply(const QString &url, const QByteArray &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    SFDownloadPreparer *_downloadPreparer;

    QString _comicName;
    QHash<QString, QString> _downloadHash;
};

#endif // DOWNLOADCONTROLLER_H
