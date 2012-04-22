#include "updatecontroller.h"
#include "sfupdater.h"
#include "sfcoverupdater.h"
#include "comicdatabase.h"

#include <QDebug>

UpdateController::UpdateController(QObject *parent) :
    QObject(parent), _state(Prepared)
{
    _updater = new SFUpdater(this);
    _coverUpdater = new SFCoverUpdater(this);

    _comicDatabase = new ComicDatabase(this);
    connect(_updater, SIGNAL(finish()), SLOT(processComic()));
    connect(_coverUpdater, SIGNAL(finish()), SLOT(processCover()));
}

void UpdateController::update()
{
    qDebug() << "UpdateController:: update start ...";
    if(_state != Prepared) qCritical() << "UpdateController::isn't prepared";
    _state = GettingComic;
    _updater->update();
}

void UpdateController::processComic()
{
    qDebug() << "UpdaterController:: processComic start ...";
    if(_comicDatabase->needUpdateCover())
    {
        _state = GettingCover;
        _coverUpdater->update(_updater->getComicList());
    }
    else
    {
        _state = Prepared;
        _comicDatabase->update(_updater->getComicList());
        qDebug() << "UpdaterController:: finish";
        emit finish();
    }
}

void UpdateController::processCover()
{
    qDebug() << "UpdaterController:: processCover start ...";
    _comicDatabase->update(_coverUpdater->getComicList());
    qDebug() << "UpdaterController:: finish";
    emit finish();
}
