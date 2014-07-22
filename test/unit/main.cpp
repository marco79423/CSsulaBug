#include <QTest>

#include "convertztest.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(core_resource);

    int ret = 0;

    ConvertZTest test;
    ret += QTest::qExec(&test, argc, argv);

    return ret;
}

