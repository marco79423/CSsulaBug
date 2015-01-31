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
    
    bool isBusy() const;
    bool get(const QString &url, const QString &referer="");
    bool get(const QStringList &urlList, const QString &referer="");
    void abort();

    QByteArray getDataImmediately(const QString &url, const QString &referer="");

private slots:

    void _onManagerReply(QNetworkReply *networkReply);

private:

    void _startAccess();
    QNetworkRequest _makeRequest(const QString &url, const QString &referer="");

private:

    QNetworkAccessManager *_networkAccessManager;

    QList<QNetworkReply*> _replyList;
    QString _referer;
};


Q_DECLARE_METATYPE(QNetworkReply *)

#endif // NETWORKACCESSOR_H
