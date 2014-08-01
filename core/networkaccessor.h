#ifndef NETWORKACCESSOR_H
#define NETWORKACCESSOR_H

#include <QObject>
#include <QStringList>
#include <QQueue>
#include <QNetworkReply>

class QNetworkAccessManager;
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
    void finish(const int &id, const bool &error);

private slots:

    void _onManagerReply(QNetworkReply *networkReply);

private:

    struct _Task
    {
        int id;
        QStringList urlList;
        QList<QNetworkReply*> replyList;
    };

    QNetworkAccessManager *_networkAccessManager;
    int _idCount;
    bool _isAccessing;
    QQueue<_Task> _taskQueue;
    _Task _currentTask;

    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url);

};


Q_DECLARE_METATYPE(QNetworkReply *)

#endif // NETWORKACCESSOR_H
