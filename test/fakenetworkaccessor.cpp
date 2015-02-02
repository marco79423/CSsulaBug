#include "fakenetworkaccessor.h"
#include <QTimer>

FakeNetworkAccessor::FakeNetworkAccessor(QObject *parent) : QObject(parent)
{

}

bool FakeNetworkAccessor::isBusy() const
{
    return false;
}

bool FakeNetworkAccessor::get(const QString &url, const QString &referer)
{
    Q_UNUSED(url)
    Q_UNUSED(referer)
}

bool FakeNetworkAccessor::get(const QStringList &urlList, const QString &referer)
{
    Q_UNUSED(urlList)
    Q_UNUSED(referer)
}

void FakeNetworkAccessor::abort()
{

}

QByteArray FakeNetworkAccessor::getDataImmediately(const QString &url, const QString &referer)
{

}

