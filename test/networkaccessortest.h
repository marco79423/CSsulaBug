#ifndef NETWORKACCESSORTEST_H
#define NETWORKACCESSORTEST_H

#include <QObject>

class NetworkAccessorTest : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase();
    void get();
    void abort();
    void getDataImmediately();
};

#endif // NETWORKACCESSORTEST_H
