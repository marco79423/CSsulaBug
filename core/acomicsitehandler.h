#ifndef ACOMICSITEHANDLER_H
#define ACOMICSITEHANDLER_H

#include <QObject>

#include "globals.h"

class AComicSiteHandler : public QObject
{
    Q_OBJECT

public:

    virtual QList<StringPair> getChapters(const QString &comicKey) = 0;
    virtual QStringList getImageUrls(const QString &comicKey, const QString &chapterKey) = 0;

    virtual QString getReferer() const { return ""; }

signals:

    void comicInfoSignal(const StringHash &info);
    void updateFinishedSignal();

public slots:

    virtual void update() = 0;

protected:

    explicit AComicSiteHandler(QObject *parent = 0):QObject(parent){}
};

#endif // ACOMICSITEHANDLER_H
