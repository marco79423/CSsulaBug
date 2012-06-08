#include "maincontroller.h"
#include "updatehandler.h"
#include "downloadhandler.h"

MainController::MainController(QObject *parent) :
    QObject(parent), _updateHandler(NULL), _downloadHandler(NULL)
{
    _setConnection();
}

void MainController::setUpdateHandler(UpdateHandler *updateHandler)
{
    _updateHandler = updateHandler;
}

void MainController::setDownloadHandler(DownloadHandler *downloadHandler)
{
    _downloadHandler = downloadHandler;
}

void MainController::update()
{
    _updateHandler->update();
}

void MainController::download(const QString &name, const QString &dstDir)
{
    _downloadHandler->download(name, dstDir);
}

void MainController::_setConnection()
{
    connect(_updateHandler, SIGNAL(updateInfo(const QHash<QString,QString>&)),
            SIGNAL(updateInfo(const QHash<QString,QString>&)));
    connect(_updateHandler, SIGNAL(updateFinish()), SIGNAL(updateFinish()));
    connect(_downloadHandler, SIGNAL(downloadInfo(const QHash<QString,QString>&)),
            SIGNAL(downloadInfo(const QHash<QString,QString>&)));
    connect(_downloadHandler, SIGNAL(downloadFinish()), SIGNAL(downloadFinish()));
}


