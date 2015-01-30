#ifndef MOCKNETWORKACCESSOR_H
#define MOCKNETWORKACCESSOR_H

#include <gmock/gmock.h>
#include <anetworkaccessor.h>
#include <QStringList>

class MockNetworkAccessor: public ANetworkAccessor
{
public:

    MOCK_METHOD2(get, int(const QString &url, const QString &referer));
    MOCK_METHOD2(get, int(const QStringList &urlList, const QString &referer));
    MOCK_METHOD1(abort, void(const int &id));
    MOCK_METHOD2(getDataImmediately, QString(const QString &url, const QString &referer));
};

#endif // MOCKNETWORKACCESSOR_H

