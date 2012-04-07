#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

#include <QObject>

class UpdateController : public QObject
{
    Q_OBJECT

public:

    explicit UpdateController(QObject *parent = 0);
    
signals:
    
    void finish();

public slots:
    
};

#endif // UPDATECONTROLLER_H
