#ifndef SFDOWNLOADHANDLER_H
#define SFDOWNLOADHANDLER_H

#include "adownloadhandler.h"
#include "filedownloader.h"
#include "convertz.h"

class NetworkAccessor;

class SFDownloadHandler : public ADownloadHandler
{
    Q_OBJECT

public:

    explicit SFDownloadHandler(QObject *parent = 0);
    virtual bool isReady() const;

public slots:

    virtual void download(const QString &key, const QString &dstDir);

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id, const bool &error);

    void _onDownloaderInfo(const StringHash &downloaderInfo);
    void _onDownloaderFinish();

private:

    enum State { NothingDoing, ChapterUrlListing, TaskMaking, Downloading};

    State _currentState;
    NetworkAccessor *_networkAccessor;
    QHash<QString, QString> _taskInfo;
    QStringList _chapterUrlList;

    FileDownloader *_fileDownloader;
    FileDownloader::Task _task;
    ConvertZ _convertz;

    void _clear();
    void _startProcess(const State &state);
    void _getComicName(const QString &html);
    void _listChapters(const QString &html);
    void _makeTask(const QString &url, const QString &html);
};

#endif // SFDOWNLOADHANDLER_H
