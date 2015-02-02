#include "servicetest.h"

#include <service.h>

#include <QtTest>
#include <QSortFilterProxyModel>
#include <QModelIndex>

#include <QDebug>

ServiceTest::ServiceTest(QObject *parent)
    :QObject(parent), _service(new Service)
{
}

void ServiceTest::update()
{
}
