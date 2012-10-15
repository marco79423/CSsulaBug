#include "core.h"
#include "sfdownloadhandler.h"
#include "comicmodel.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    _model = new ComicModel(this);
    _downloadHandler = new SFDownloadHandler(this);

    connect(_model, SIGNAL(updateFinish()), SIGNAL(updateFinish()));
}

ComicModel* Core::model() const
{
    return _model;
}

void Core::update()
{
    _model->update();
}

void Core::download(const QString &key, const QString &dstDir)
{
    _downloadHandler->download(key, dstDir);
}




