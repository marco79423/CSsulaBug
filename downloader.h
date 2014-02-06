#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QHash>
#include <QStringList>

class NetworkAccessor;
class QNetworkReply;

class Downloader : public QObject
{
    Q_OBJECT

public:

    //Task => (Url, FilePath)
    typedef QHash<QString, QString> Task;

    explicit Downloader(QObject *parent = 0);

    void d_test();

signals:
    
    void info(const QHash<QString, QString> &downloadInfo);
    void finish();

public slots:

    int download(const Task &task);

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id);

private:

    NetworkAccessor *_networkAccessor;
    QHash<int, Task> _taskHash;
};

#endif // DOWNLOADER_H
