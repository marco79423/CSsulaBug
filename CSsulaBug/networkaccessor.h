#ifndef NETWORKACCESSOR_H
#define NETWORKACCESSOR_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QQueue>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class NetworkAccessor : public QObject
{
    Q_OBJECT

public:

    explicit NetworkAccessor(QObject *parent = 0);
    
    void get(const int &id, const QString &url);
    void get(const int &id, const QStringList &urlList);

signals:
    
    void reply(const int &id, QNetworkReply *networkReply);
    void finish(const int &id);

private slots:

    void onManagerFinish(QNetworkReply *networkReply);

private:

    struct Task
    {
        int id;
        QList<QString> urlList;
    };

    QNetworkAccessManager *_networkAccessManager;
    QQueue<Task> _taskQueue;

    bool _isAccessing;

    void _initialize();
    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url);

};

#endif // NETWORKACCESSOR_H
