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

    bool download(const Task &task, const QString &referer="");

signals:
    
    void downloadInfoSignal(const QVariantMap &downloadInfo);
    void finishSignal();

public slots:

    void abort();

private slots:

    void _onAccessorReply(QNetworkReply *reply);
    void _onAccessorFinish();

private:

    Task _currentTask;
    int _taskSize;

    QString _referer;

    ANetworkAccessor *_networkAccessor;

    bool _saveFile(const QByteArray& data, const QString& filePath);
};

#endif // FILEDOWNLOADER_H
