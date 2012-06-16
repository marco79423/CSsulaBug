#ifndef SFDOWNLOADHANDLER_H
#define SFDOWNLOADHANDLER_H

#include "downloadhandler.h"
#include "downloader.h"

class NetworkAccessor;

class SFDownloadHandler : public DownloadHandler
{
    Q_OBJECT

public:

    explicit SFDownloadHandler(QObject *parent = 0);

public slots:

    virtual bool isReady() const;
    virtual void download(const QString &key, const QString &dstDir);

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id);

    void _onDownloaderFinish();

private:

    enum State { NothingDoing, ChapterUrlListing, TaskMaking, Downloading};

    State _currentState;
    NetworkAccessor *_networkAccessor;
    Downloader *_downloader;
    Downloader::Task _task;
    QString _key;
    QString _dstDir;
    QString _comicName;
    QStringList _chapterUrlList;

    void _setConnection();
    void _startProcess(const State &state);
    void _getComicName(const QString &html);
    void _listChapters(const QString &html);
    void _makeTask(const QString &url, const QString &html);
};

#endif // SFDOWNLOADHANDLER_H
