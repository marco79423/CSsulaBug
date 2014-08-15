#ifndef COMICINFOSERVICE_H
#define COMICINFOSERVICE_H

#include <QThread>

#include "acomicinfoservice.h"
#include "convertz.h"

class AComicSiteHandler;
class ComicModel;

class ComicInfoService : public AComicInfoService
{
    Q_OBJECT

public:
    explicit ComicInfoService(AComicSiteHandler *comicSiteHandler, QObject *parent = 0);

    virtual QSortFilterProxyModel* getModel() const;

    ~ComicInfoService();

signals:

    void _update();

public slots:

    virtual void setFilter(const QString &pattern);
    virtual QString getKey(const int index) const;


private:

    AComicSiteHandler *_comicSiteHandler;
    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;
    ConvertZ _convertz;

    QThread _updateThread;
};

#endif // COMICINFOSERVICE_H
