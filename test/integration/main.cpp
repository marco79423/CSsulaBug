#include <QCoreApplication>
#include <QTest>

#include "filesavertest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    int ret = 0;

    FileSaverTest test;
    ret += QTest::qExec(&test, argc, argv);

    return ret;
}
