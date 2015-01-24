#include "servicetest.h"

#include "stubcomicsitehandler.h"
#include <service.h>

#include <QtTest>
#include <QSortFilterProxyModel>
#include <QModelIndex>

#include <QDebug>

ServiceTest::ServiceTest(QObject *parent)
    :QObject(parent), _service(new Service)
{
    _service->addComicSiteHandler(new StubComicSiteHandler);
}

void ServiceTest::update()
{
    QSignalSpy updateFinishSpy(_service, SIGNAL(updateFinishedSignal()));

    _service->update();

    while(updateFinishSpy.size() == 0)
        updateFinishSpy.wait(100);

    QSortFilterProxyModel *model = _service->getComicModel();
    model->sort(0);
    for(int i = 0; i < 3; i++)
    {
        QModelIndex index = model->index(i, 0);
        QCOMPARE(model->data(index, 0).toString(), QString("coverUrl%1").arg(i));
        QCOMPARE(model->data(index, 1).toString(), QString("name%1").arg(i));
        QCOMPARE(model->data(index, 2).toString(), QString("key%1").arg(i));
        QCOMPARE(model->data(index, 3).toString(), QString("Stub ComicSiteHandler"));
        QCOMPARE(model->data(index, 4).toString(), QString("type%1").arg(i));
        QCOMPARE(model->data(index, 5).toString(), QString("author%1").arg(i));
        QCOMPARE(model->data(index, 6).toString(), QString("updateStatus%1").arg(i));;

    }
}
