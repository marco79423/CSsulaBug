#include <gmock/gmock.h>
#include <qtTest>
#include <filedownloader.h>
#include "mocknetworkaccessor.h"

using ::testing::InSequence;
using ::testing::Return;

TEST(FileDownloader, download)
{
    /*QString u1 = "url1", u2 = "url2";
    QString f1 = "file1", f2 = "file2";
    QByteArray d1 = "data1", d2 = "data2";

    FileDownloader::Task task;
    task[u1] = f1;
    task[u2] = f2;

    MockFileSaver *mockFileSaver = new MockFileSaver;

    EXPECT_CALL(*mockFileSaver, saveFile(d1, f1))
        .WillOnce(Return(AFileSaver::Success));
    EXPECT_CALL(*mockFileSaver, saveFile(d2, f2))
        .WillOnce(Return(AFileSaver::Success));

    MockNetworkAccessor *mockNetworkAccessor = new MockNetworkAccessor;
    QStringList keys = task.keys();
    QString referer = "";
    EXPECT_CALL(*mockNetworkAccessor, get(keys, referer))
            .WillOnce(Return(1));

    FileDownloader fileDownloader(NULL, mockFileSaver, mockNetworkAccessor);

    int id = fileDownloader.download(task);
    QMetaObject::invokeMethod(mockNetworkAccessor, "replySignal", Q_ARG(const int&, id), Q_ARG(const QString&, u1), Q_ARG(const QByteArray&, d1));
    QMetaObject::invokeMethod(mockNetworkAccessor, "replySignal", Q_ARG(const int&, id), Q_ARG(const QString&, u2), Q_ARG(const QByteArray&, d2));

    QMetaObject::invokeMethod(mockNetworkAccessor, "finishSignal", Q_ARG(const int&, id));

    QSignalSpy finishSpy(&fileDownloader, SIGNAL(finishSignal(const int&)));
    QMetaObject::invokeMethod(mockNetworkAccessor, "finishSignal", Q_ARG(const int&, id));
    EXPECT_EQ(1, finishSpy.size());
    EXPECT_EQ(id, finishSpy[0][0].toInt());*/
}
