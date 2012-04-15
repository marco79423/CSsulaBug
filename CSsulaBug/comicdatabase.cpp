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
    if(!query.prepare("CREATE TABLE IF NOT EXISTS comics"
                  "(site, key, name, type, author,"
                  "lastUpdated, description);"))

    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create comics table";

    //create covers table
    query.prepare("CREATE TABLE IF NOT EXISTS covers"
                  "(site, key, cover BLOB);");
    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create covers table";


    //create unique index uniqueKey
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS uniqueKey"
                  "ON comics(site, key);");

    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create index uniqueKey"
                    << query.lastError().text();

    //create unique index uniqueKey2
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS uniqueKey2"
                  "ON covers(site, key);");

    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create index uniqueKey2"
                    << query.lastError().text();
}

bool ComicDatabase::needUpdateCover() const
{
    qDebug() << "ComicDatabase::needUpdateCover start ...";
    QSqlQuery query;
    query.prepare("SELECT count(key) FROM covers WHERE NOT EXISTS"
                  "(SELECT * FROM comics"
                  "WHERE covers.site=comics.site and covers.key=comics.site);");

    query.next();
    if(!query.exec())
        qCritical() << "ComicDatabase:: query is failed.";
    return query.value(0).toInt() == 1;
}

void ComicDatabase::update(QList<ComicInfo> comicInfoList)
{
    qDebug() << "ComicDatabase::update start ...";
    foreach(ComicInfo comicInfo, comicInfoList)
    {}
}

QSqlQuery ComicDatabase::doQuery(const QString &query, const QString &error)
{
    qDebug() << "ComicDatabase::doQuery start ...";
    QSqlQuery sqlQuery;

    if(!sqlQuery.prepare(query))
        qCritical() << "ComicDatabase::prepare is failed";

    if(!sqlQuery.exec())
        qCritical() << "ComicDatabase::"
                    << error << sqlQuery.lastError().text();
    return sqlQuery;
}

