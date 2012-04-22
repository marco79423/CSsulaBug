#include "comicdatabase.h"
#include <QtSql>
#include <QDir>
#include <QDebug>

ComicDatabase::ComicDatabase(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/cssulabug.db");
    if(!db.open())
    {
        qDebug() << db.lastError();
    }

    QSqlQuery query;

    //create comics table
    qDebug() << "ComicDatabase::Create comic table";
    query.prepare("CREATE TABLE IF NOT EXISTS comics(site, key, name, type, author,"
                  "lastUpdated, description);");
    if(!query.exec())
        qCritical() << "ComicDatabase::" << query.lastError().text();

    //create covers table
    qDebug() << "ComicDatabase::Create covers table";
    query.prepare("CREATE TABLE IF NOT EXISTS covers(site, key, cover BLOB);");
    if(!query.exec())
        qCritical() << "ComicDatabase::" << query.lastError().text();

    //create unique index uniqueKey
    qDebug() << "ComicDatabase::Create unique index uniqueKey";
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS uniqueKey ON "
                  "comics(site, key);");
    if(!query.exec())
        qCritical() << "ComicDatabase::" << query.lastError().text();

    //create unique index uniqueKey
    qDebug() << "ComicDatabase::Create unique index uniqueKey";
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS uniqueKey2 ON "
                  "covers(site, key);");
    if(!query.exec())
        qCritical() << "ComicDatabase::" << query.lastError().text();
}

bool ComicDatabase::needUpdateCover() const
{
    qDebug() << "ComicDatabase::needUpdateCover start ...";
    QSqlQuery query("SELECT count(key) FROM covers WHERE NOT EXISTS "
                    "(SELECT * FROM comics WHERE covers.site=comics.site "
                    "and covers.key=comics.site);");

    if(query.next())
        return query.value(0).toInt() == 1;
}

void ComicDatabase::update(QList<ComicInfo> comicInfoList)
{
    qDebug() << "ComicDatabase::update start ...";
    foreach(ComicInfo comicInfo, comicInfoList)
    {
        QSqlQuery query;

        qDebug() << "ComicDatabase:: insert comic " << comicInfo.getInfo();
        query.prepare("REPLACE INTO comics VALUES(:site, :key, :name,"
                      ":type, :author, :lastUpdated, :description)");
        query.bindValue(":site", comicInfo.getSite());
        query.bindValue(":key", comicInfo.getKey());
        query.bindValue(":name", comicInfo.getName());
        query.bindValue(":type", comicInfo.getType());
        query.bindValue(":author", comicInfo.getAuthor());
        query.bindValue(":lastUpdated", comicInfo.getLastUpdated());
        query.bindValue(":description", comicInfo.getDescription());

        if(!query.exec())
            qCritical() << "ComicDatabase::" << query.lastError().text();

        if(comicInfo.hasCover())
        {
            qDebug() << "ComicDatabase:: insert cover in " << comicInfo.getKey();
            query.prepare("REPLACE INTO covers VALUES(:site, :key, :cover)");
            query.bindValue(":site", comicInfo.getSite());
            query.bindValue(":key", comicInfo.getKey());
            query.bindValue(":cover", comicInfo.getCover());
            if(!query.exec())
                qCritical() << "ComicDatabase::" << query.lastError().text();
        }
    }
}
