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
    
    void downloadInfoSignal(const int &id, const QVariantMap &downloadInfo);
    void finishSignal(const int &id);

public slots:

    int download(const Task &task, const QString &referer="");

private slots:

    void _onAccessorReply(const int &id, const QString &url, const QByteArray &data);
    void _onAccessorFinish(const int &id);

private:

    AFileSaver *_fileSaver;
    ANetworkAccessor *_networkAccessor;
    QHash<int, Task> _taskHash;
};

#endif // FILEDOWNLOADER_H
