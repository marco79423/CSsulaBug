#include "networkaccessortest.h"

#include <networkaccessor.h>

#include <QtTest>
#include <QDebug>
#include <QNetworkReply>

void NetworkAccessorTest::get()
{
    NetworkAccessor *networkAccessor = new NetworkAccessor(this);
    QSignalSpy replySpy(networkAccessor, SIGNAL(replySignal(QNetworkReply*)));
    QSignalSpy finishSpy(networkAccessor, SIGNAL(finishSignal()));

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    QVERIFY(networkAccessor->get(url));

    while(replySpy.size() == 0)
        replySpy.wait(100);

    while(finishSpy.size() == 0)
        finishSpy.wait(100);

    QList<QVariant> args = replySpy.takeFirst();
    QNetworkReply *reply = args.at(0).value<QNetworkReply*>();


    QVERIFY(reply->error() == QNetworkReply::NoError);

    QFile file(":/images/marco.jpg");
    QVERIFY(file.open(QFile::ReadOnly));
    QCOMPARE(reply->readAll(), file.readAll());
}

void NetworkAccessorTest::abort()
{
    NetworkAccessor *networkAccessor = new NetworkAccessor(this);
    QSignalSpy replySpy(networkAccessor, SIGNAL(replySignal(QNetworkReply*)));
    QSignalSpy finishSpy(networkAccessor, SIGNAL(finishSignal()));

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    QVERIFY(networkAccessor->get(url));
    networkAccessor->abort();

    while(replySpy.size() == 0)
        replySpy.wait(100);

    while(finishSpy.size() == 0)
        finishSpy.wait(100);

    QList<QVariant> args = replySpy.takeFirst();
    QNetworkReply *reply = args.at(0).value<QNetworkReply*>();

    QVERIFY(reply->error() == QNetworkReply::OperationCanceledError);
}

void NetworkAccessorTest::getDataImmediately()
{
    NetworkAccessor *networkAccessor = new NetworkAccessor(this);

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    QByteArray data = networkAccessor->getDataImmediately(url);

    QFile file(":/images/marco.jpg");
    QVERIFY(file.open(QFile::ReadOnly));
    QCOMPARE(data, file.readAll());
}
