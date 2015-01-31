#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QHash>

#include "globals.h"
#include "networkaccessor.h"

class QNetworkReply;

class FileDownloader : public QObject
{
    Q_OBJECT

public:

    //Task => (Url, FilePath)
    typedef QHash<QString, QString> Task;

    explicit FileDownloader(QObject *parent = 0, ANetworkAccessor *networkAccessor=new NetworkAccessor);

signals:
    
    void downloadInfoSignal(const QVariantMap &downloadInfo);
    void finishSignal();

public slots:

    bool download(const Task &task, const QString &referer="");
    void abort();

private slots:

    void _onAccessorReply(QNetworkReply *reply);
    void _onAccessorFinish();

private:

    Task _currentTask;
    int _taskSize;

    ANetworkAccessor *_networkAccessor;

    bool _saveFile(const QByteArray& data, const QString& filePath);
};

#endif // FILEDOWNLOADER_H
