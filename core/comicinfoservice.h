#ifndef COMICINFOSERVICE_H
#define COMICINFOSERVICE_H

#include "acomicinfoservice.h"
#include "convertz.h"

class AUpdateHandler;
class ComicModel;

class ComicInfoService : public AComicInfoService
{
    Q_OBJECT

public:
    explicit ComicInfoService(AUpdateHandler *updateHandler, QObject *parent = 0);

    virtual QSortFilterProxyModel* getModel() const;

public slots:

    virtual void setFilter(const QString &pattern);
    virtual QString getKey(const int index) const;


private:

    AUpdateHandler *_updateHandler;
    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;
    ConvertZ _convertz;
};

#endif // COMICINFOSERVICE_H
