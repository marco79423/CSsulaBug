#ifndef A_DOWNLOAD_HANDLER_H
#define A_DOWNLOAD_HANDLER_H

#include <QObject>

#include "globals.h"

class ADownloadHandler : public QObject
{
    Q_OBJECT

public:

	virtual bool isReady() const { return true;}
    
signals:

    void info(const StringHash &info);
    void finish();

public slots:

    virtual void download(const QString &key, const QString &dstDir) = 0;

protected:

	explicit ADownloadHandler(QObject *parent = 0) :QObject(parent){}
};

#endif // A_DOWNLOAD_HANDLER_H
