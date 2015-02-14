#ifndef FAKECOMICSITEHANDLER_H
#define FAKECOMICSITEHANDLER_H

#include <comicsitehandler/acomicsitehandler.h>

#include "fakedata.h"

class FakeComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT
public:

    explicit FakeComicSiteHandler(QObject *parent=NULL);

    virtual QString getComicSiteName() const;

    virtual QList<StringPair> getChapters(const QString &comicKey) = 0;
    virtual QStringList getImageUrls(const QString &comicKey, const QString &chapterKey) = 0;

    virtual QString getReferer() const;

public slots:

    virtual void collectComicInfos();

private slots:

    void onComicInfoSignal();

private:

    FakeData _fakeData;
};

#endif // FAKECOMICSITEHANDLER_H
