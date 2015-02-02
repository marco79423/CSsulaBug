#ifndef FAKEDATA_H
#define FAKEDATA_H

#include <QVariantMap>
#include <globals.h>

class FakeData
{
public:
    FakeData();

    QVariantMap getComicInfo(const int &index, const bool &withoutChapters=true);
    int getComicInfoCount();
    QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

    QList<StringPair> getChapters(const QString &comicKey);

private:

    QList<QVariantMap> _comicInfos;
};

#endif // FAKEDATA_H
