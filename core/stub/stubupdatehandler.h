#ifndef STUBUPDATEHANDLER_H
#define STUBUPDATEHANDLER_H

#include "../aupdatehandler.h"

class StubUpdateHandler : public AUpdateHandler
{
    Q_OBJECT

public:
    explicit StubUpdateHandler(QObject *parent = 0);

public slots:

    virtual void update();
};

#endif // STUBUPDATEHANDLER_H
