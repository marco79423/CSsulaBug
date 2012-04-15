#ifndef COMICDATABASE_H
#define COMICDATABASE_H

#include <QObject>
#include <QHash>

#include <comicinfo.h>

class ComicDatabase : public QObject
{
    Q_OBJECT

public:

    explicit ComicDatabase(QObject *parent = 0);

    bool needUpdateCover() const;

public slots:

    void update(QList<ComicInfo> comicInfo);

};

#endif // COMICDATABASE_H
