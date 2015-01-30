#ifndef NETWORKACCESSOR_H
#define NETWORKACCESSOR_H

#include <QObject>
#include <QStringList>
#include <QQueue>
#include <QNetworkReply>

#include "anetworkaccessor.h"

class QNetworkAccessManager;
class QNetworkRequest;

class NetworkAccessor : public ANetworkAccessor
{
    Q_OBJECT

public:

    explicit NetworkAccessor(QObject *parent = 0);
    
    int get(const QString &url, const QString &referer="");
    int get(const QStringList &urlList, const QString &referer="");
    void abort(const int &id);

    QString getDataImmediately(const QString &url, const QString &referer="");

private slots:

    void _onManagerReply(QNetworkReply *networkReply);

private:

    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url, const QString &referer="");

private:

    struct _Task
    {
        int id;
        QStringList urlList;
        QString referer;
        QList<QNetworkReply*> replyList;
    };

    static int _idCount;
    QNetworkAccessManager *_networkAccessManager;
    QQueue<_Task> _taskQueue;
};


Q_DECLARE_METATYPE(QNetworkReply *)

#endif // NETWORKACCESSOR_H
