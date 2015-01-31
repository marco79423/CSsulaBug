#ifndef MOCKNETWORKACCESSOR_H
#define MOCKNETWORKACCESSOR_H

#include <gmock/gmock.h>
#include <anetworkaccessor.h>
#include <QStringList>

class MockNetworkAccessor: public ANetworkAccessor
{
public:

    MOCK_METHOD0(isBusy, bool());
    MOCK_METHOD2(get, bool(const QString &url, const QString &referer));
    MOCK_METHOD2(get, bool(const QStringList &urlList, const QString &referer));
    MOCK_METHOD0(abort, void());
    MOCK_METHOD2(getDataImmediately, QByteArray(const QString &url, const QString &referer));
};

#endif // MOCKNETWORKACCESSOR_H

