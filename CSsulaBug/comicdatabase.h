#ifndef COMICDATABASE_H
#define COMICDATABASE_H

#include <QObject>
#include <QHash>

class ComicDatabase : public QObject
{
    Q_OBJECT

public:

    explicit ComicDatabase(QObject *parent = 0);
    
signals:
    
public slots:

    void add(QHash<QString, QString> comicInfo);
    
};

#endif // COMICDATABASE_H
