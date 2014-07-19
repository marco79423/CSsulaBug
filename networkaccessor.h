#ifndef NETWORKACCESSOR_H
#define NETWORKACCESSOR_H

#include <QObject>
#include <QStringList>
#include <QQueue>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class NetworkAccessor : public QObject
{
    Q_OBJECT

public:

    explicit NetworkAccessor(QObject *parent = 0);
    
    int get(const QString &url);
    int get(const QStringList &urlList);

    void d_test();

signals:
    
    void reply(const int &id, QNetworkReply *networkReply);
    void finish(const int &id);

private slots:

    void _onManagerFinish(QNetworkReply *networkReply);

private:

    struct _Task
    {
        int id;
        QStringList urlList;
    };

    QNetworkAccessManager *_networkAccessManager;
    int _idCount;
    bool _isAccessing;
    QQueue<_Task> _taskQueue;
    _Task _currentTask;

    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url);

};

#endif // NETWORKACCESSOR_H
