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

    struct Task
    {
        QStringList urlList;
        QHash<QString, QString> pathList;
    };

    explicit Downloader(QObject *parent = 0);

signals:
    
    void finish();

public slots:

    void download(const Task &task);

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id);

private:

    NetworkAccessor *_networkAccessor;
    QHash<int, QHash<QString, QString> > _pathList;
    int _taskIdCount;

    void _setConnection();
};

#endif // DOWNLOADER_H
