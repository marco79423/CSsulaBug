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

    //create table comics
    query.prepare("CREATE TABLE IF NOT EXISTS comics"
                  "('site', 'key', 'name', 'type', 'author',"
                  "'lastUpdated', 'description', cover BLOB);");
    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create table comics";

    //create unique index
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS uniqueKey"
                  "ON comics('site', 'key')");

    if(!query.exec())
        qCritical() << "ComicDatabase::Failed to create idnex uniqueKey";

}

bool ComicDatabase::needUpdateCover() const
{
    qDebug() << "ComicDatabase:: needUpdateCover start ...";
    QSqlQuery query;
    query.prepare("SELECT count(key) != count(cover) FROM comics;");
    if(!query.exec())
        qCritical() << "ComicDatabase:: query failed.";
}

void ComicDatabase::update(QList<ComicInfo> comicInfo)
{
}
