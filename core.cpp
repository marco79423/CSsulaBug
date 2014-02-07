#include "core.h"
#include "sfdownloadhandler.h"
#include "comicmodel.h"

#include <QSortFilterProxyModel>

Core::Core(QObject *parent) :
    QObject(parent)
{
    _model = new ComicModel(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);
    _downloadHandler = new SFDownloadHandler(this);

    connect(_model, SIGNAL(updateFinish()), SIGNAL(updateFinish()));
}

QSortFilterProxyModel* Core::model() const
{
    return _proxyModel;
}

void Core::update()
{
    _model->update();
}

void Core::download(const QString &key, const QString &dstDir)
{
    _downloadHandler->download(key, dstDir);
}

void Core::setFilter(const QString &pattern)
{
    _proxyModel->setFilterRole(1);
    _proxyModel->setFilterRegExp(QRegExp(pattern, Qt::CaseInsensitive,
                                                 QRegExp::FixedString));
}

QString Core::getKey(const int index) const
{
    return _proxyModel->data(_proxyModel->index(index, 0), 2).toString();
}




