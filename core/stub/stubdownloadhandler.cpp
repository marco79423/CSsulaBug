#include "stubdownloadhandler.h"
#include <QThread>

StubDownloadHandler::StubDownloadHandler(QObject *parent)
    :ADownloadHandler(parent), _isReady(true)
{
}

bool StubDownloadHandler::isReady() const
{
    return _isReady;
}

void StubDownloadHandler::download(const QString &key, const QString &dstDir)
{
    _isReady = false;
    for(int i=10; i <= 100; i+= 10)
    {
        QThread::sleep(1);
        QHash<QString, QString> downloadInfo;
        downloadInfo["progress"] = QString::number(i);
        downloadInfo["path"] = QString("~/dirpath/%1").arg(i);
        emit info(downloadInfo);
    }

    emit finish();
    _isReady = true;
}
