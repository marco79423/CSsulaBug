#ifndef ACOMICINFOSERVICE_H
#define ACOMICINFOSERVICE_H

#include <QObject>
#include <QSortFilterProxyModel>

class AComicInfoService : public QObject
{
    Q_OBJECT

public:

    virtual QSortFilterProxyModel* getModel() const = 0;

signals:

    void updateFinish();

public slots:

    virtual void update() = 0;
    virtual void setFilter(const QString &pattern) = 0;
    virtual QString getKey(const int index) const = 0;

protected:

    explicit AComicInfoService(QObject *parent = 0):QObject(parent){}
};

#endif // ACOMICINFOSERVICE_H