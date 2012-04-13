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
    query.prepare("");
}

void ComicDatabase::add(QHash<QString, QString> comicInfo)
{

}
