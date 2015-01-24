#include <QCoreApplication>
#include <gmock/gmock.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Q_INIT_RESOURCE(core_resource);

    /*int ret = 0;

    ConvertZTest convertZTest;
    ret += QTest::qExec(&convertZTest, argc, argv);

    ServiceTest serviceTest;
    ret += QTest::qExec(&serviceTest, argc, argv);

    return ret;*/

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

