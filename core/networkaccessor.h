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

    QString getDataImmediately(const QString &url);

signals:
    
    void replySignal(const int &id, const QString &url, const QByteArray &data);
    void finishSignal(const int &id);

private slots:

    void _onManagerReply(QNetworkReply *networkReply);

private:

    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url);

private:

    struct _Task
    {
        int id;
        QStringList urlList;
    };

    static int _idCount;
    QNetworkAccessManager *_networkAccessManager;
    QQueue<_Task> _taskQueue;
};


Q_DECLARE_METATYPE(QNetworkReply *)

#endif // NETWORKACCESSOR_H
