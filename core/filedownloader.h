#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QHash>

#include "globals.h"
#include "networkaccessor.h"
#include "filesaver.h"

class QNetworkReply;

class FileDownloader : public QObject
{
    Q_OBJECT

public:

    //Task => (Url, FilePath)
    typedef QHash<QString, QString> Task;

    explicit FileDownloader(QObject *parent = 0, AFileSaver *fileSaver=new FileSaver, ANetworkAccessor *networkAccessor=new NetworkAccessor);

signals:
    
    void downloadInfoSignal(const QVariantMap &downloadInfo);
    void finishSignal();

public slots:

    int download(const Task &task, const QString &referer="");
    void abort();

private slots:

    void _onAccessorReply(const int &id, const QString &url, const QByteArray &data);
    void _onAccessorFinish(const int &id);

private:

    bool _downloading;
    Task _currentTask;
    int _taskId;
    int _counter;

    AFileSaver *_fileSaver;
    ANetworkAccessor *_networkAccessor;
};

#endif // FILEDOWNLOADER_H
