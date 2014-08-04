#ifndef STUBDOWNLOADHANDLER_H
#define STUBDOWNLOADHANDLER_H

#include "../adownloadhandler.h"

class StubDownloadHandler : public ADownloadHandler
{
    Q_OBJECT

public:
    explicit StubDownloadHandler(QObject *parent = 0);

    virtual bool isReady() const;

public slots:

    virtual void download(const QString &key, const QString &dstDir);


private:

    bool _isReady;
};

#endif // STUBDOWNLOADHANDLER_H
