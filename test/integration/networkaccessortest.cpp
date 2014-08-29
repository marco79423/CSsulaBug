#include "networkaccessortest.h"

#include <networkaccessor.h>

#include <QtTest>
#include <QDebug>
#include <QNetworkReply>

void NetworkAccessorTest::get()
{
    NetworkAccessor *networkAccessor = new NetworkAccessor(this);
    QSignalSpy spy1(networkAccessor, SIGNAL(replySignal(const int&, QNetworkReply*)));
    QSignalSpy spy2(networkAccessor, SIGNAL(finishSignal(const int&, const bool&)));

    //const int id = networkAccessor->get("http://comic.sfacg.com/Catalog/");
    const int id = networkAccessor->get("http://marco79423.twbbs.org/images/author/marco.jpg");


    while(spy2.size() == 0)
        spy2.wait(1000);

    QList<QVariant> args2 = spy2.takeFirst();
    QVERIFY(args2.at(0).toInt() == id);
    QVERIFY(args2.at(1).toBool() != true);

    QList<QVariant> args = spy1.takeFirst();
    QVERIFY(args.at(0).toInt() == id);

    QNetworkReply *reply = args.at(1).value<QNetworkReply*>();

    QFile file(":/images/marco.jpg");
    QVERIFY(file.open(QFile::ReadOnly));
    QCOMPARE(reply->readAll(), file.readAll());
}
