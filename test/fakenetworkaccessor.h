#ifndef FAKENETWORKACCESSOR_H
#define FAKENETWORKACCESSOR_H

#include <QObject>

class FakeNetworkAccessor : public QObject
{
    Q_OBJECT
public:
    explicit FakeNetworkAccessor(QObject *parent = 0);

    bool isBusy() const;
    bool get(const QString &url, const QString &referer="");
    bool get(const QStringList &urlList, const QString &referer="");
    void abort();

    QByteArray getDataImmediately(const QString &url, const QString &referer="");
};

#endif // FAKENETWORKACCESSOR_H
