#ifndef STUBCOMICSITEHANDLER_H
#define STUBCOMICSITEHANDLER_H

#include <acomicsitehandler.h>

class StubComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT

public:

    QString getComicSiteName() const;
    QList<StringPair> getChapters(const QString &comicKey);
    QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

public slots:

    void update();

private slots:

    void _onUpdate();
};

#endif // STUBCOMICSITEHANDLER_H
