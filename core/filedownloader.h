#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QHash>

#include "globals.h"

class AFileSaver;
class NetworkAccessor;
class QNetworkReply;

class FileDownloader : public QObject
{
    Q_OBJECT

public:

    //Task => (Url, FilePath)
    typedef QHash<QString, QString> Task;

    explicit FileDownloader(AFileSaver *fileSaver, QObject *parent = 0);

signals:
    
    void downloadInfoSignal(const int &id, const StringHash &downloadInfo);
    void finishSignal(const int &id);

public slots:

    int download(const Task &task);

private slots:

    void _onAccessorReply(const int &id, const QString &url, const QByteArray &data);
    void _onAccessorFinish(const int &id);

private:

    AFileSaver *_fileSaver;
    NetworkAccessor *_networkAccessor;
    QHash<int, Task> _taskHash;
};

#endif // FILEDOWNLOADER_H
