#ifndef ANETWORKACCESSOR_H
#define ANETWORKACCESSOR_H

#include <QObject>
#include <QNetworkReply>

class ANetworkAccessor : public QObject
{
    Q_OBJECT

public:

    explicit ANetworkAccessor(QObject *parent = 0): QObject(parent){}

    virtual bool isBusy() const = 0;
    virtual bool get(const QString &url, const QString &referer="") = 0;
    virtual bool get(const QStringList &urlList, const QString &referer="") = 0;
    virtual void abort() = 0;

    virtual QByteArray getDataImmediately(const QString &url, const QString &referer="") = 0;

signals:

    void replySignal(QNetworkReply* reply);
    void finishSignal();
};

#endif // ANETWORKACCESSOR_H
