#ifndef ANETWORKACCESSOR_H
#define ANETWORKACCESSOR_H

#include <QObject>

class ANetworkAccessor : public QObject
{
    Q_OBJECT

public:

    explicit ANetworkAccessor(QObject *parent = 0): QObject(parent){}

    virtual int get(const QString &url, const QString &referer="") = 0;
    virtual int get(const QStringList &urlList, const QString &referer="") = 0;
    virtual void abort(const int &id) = 0;

    virtual QString getDataImmediately(const QString &url, const QString &referer="") = 0;

signals:

    void replySignal(const int &id, const QString &url, const QByteArray &data);
    void finishSignal(const int &id);
};

#endif // ANETWORKACCESSOR_H
