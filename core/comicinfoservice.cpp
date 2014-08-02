#include "comicinfoservice.h"
#include "aupdatehandler.h"
#include "comicmodel.h"

#include <QSortFilterProxyModel>

ComicInfoService::ComicInfoService(AUpdateHandler *updateHandler, QObject *parent) :
    AComicInfoService(parent), _updateHandler(updateHandler)
{
    _updateHandler->setParent(this);

    _model = new ComicModel(_updateHandler, this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);

    connect(_model, SIGNAL(updateFinish()), SIGNAL(updateFinish()));
}


QSortFilterProxyModel *ComicInfoService::getModel() const
{
    return _proxyModel;
}


void ComicInfoService::update()
{
    _model->update();
}

void ComicInfoService::setFilter(const QString &pattern)
{
    QString tpattern = _convertz.convertToTraditional(pattern);
    _proxyModel->setFilterRole(1);
    _proxyModel->setFilterRegExp(QRegExp(tpattern, Qt::CaseInsensitive, QRegExp::FixedString));
}

QString ComicInfoService::getKey(const int index) const
{
    return _proxyModel->data(_proxyModel->index(index, 0), 2).toString();
}
