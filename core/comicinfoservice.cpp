#include "comicinfoservice.h"
#include "acomicsitehandler.h"
#include "comicmodel.h"

#include <QSortFilterProxyModel>

ComicInfoService::ComicInfoService(AComicSiteHandler *comicSiteHandler, QObject *parent) :
    AComicInfoService(parent), _comicSiteHandler(comicSiteHandler)
{
    _model = new ComicModel(this);

    connect(_comicSiteHandler, SIGNAL(comicInfoSignal(const StringHash&)), _model,  SLOT(_insertOneEntry(const StringHash&)));
    connect(_comicSiteHandler, SIGNAL(updateFinishedSignal()), this, SIGNAL(updateFinishedSignal()));
    connect(&_updateThread, SIGNAL(finished()), _comicSiteHandler, SLOT(deleteLater()));

    connect(this, SIGNAL(_update()), _comicSiteHandler, SLOT(updateComicInfos()));

    _comicSiteHandler->moveToThread(&_updateThread);
    _updateThread.start();

    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);

    emit _update();
}


QSortFilterProxyModel *ComicInfoService::getModel() const
{
    return _proxyModel;
}

ComicInfoService::~ComicInfoService()
{
    _updateThread.quit();
    _updateThread.wait();
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
