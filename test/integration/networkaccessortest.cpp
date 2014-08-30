#include "networkaccessortest.h"

#include <networkaccessor.h>

#include <QtTest>
#include <QDebug>
#include <QNetworkReply>

void NetworkAccessorTest::get()
{
    NetworkAccessor *networkAccessor = new NetworkAccessor(this);
    QSignalSpy spy1(networkAccessor, SIGNAL(replySignal(const int&, const QString&, const QByteArray&)));
    QSignalSpy spy2(networkAccessor, SIGNAL(finishSignal(const int&)));

    QString url = "http://marco79423.twbbs.org/images/author/marco.jpg";
    const int id = networkAccessor->get(url);

    while(spy2.size() == 0)
        spy2.wait(1000);

    QList<QVariant> args2 = spy2.takeFirst();
    QCOMPARE(args2.at(0).toInt(), id);

    QList<QVariant> args = spy1.takeFirst();
    QCOMPARE(args.at(0).toInt(), id);
    QCOMPARE(args.at(1).toString(), url);

    QFile file(":/images/marco.jpg");
    QVERIFY(file.open(QFile::ReadOnly));
    QCOMPARE(args.at(2).toByteArray(), file.readAll());
}
