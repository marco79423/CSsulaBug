#include "lister.h"
#include "ui_lister.h"
#include "delegate.h"
#include <QtSql>
#include <QDir>

#include <QDebug>

Lister::Lister(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Lister)
{
    _ui->setupUi(this);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QDir::homePath() + "/.cug");

    if( !database.open() )
    {
      qDebug() << database.lastError();
      qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    _sqlQueryModel = new QSqlQueryModel(this);
    _sqlQueryModel->setQuery( "SELECT * FROM work" );

    _ui->tableView->setModel(_sqlQueryModel);
    //_ui->tableView->setSortingEnabled(true);
    _ui->tableView->setSelectionBehavior(QTableView::SelectRows);
    //_ui->tableView->setVerticalScrollMode(QTableView::ScrollPerPixel);
    _ui->tableView->setItemDelegate(new Delegate(this));
}

Lister::~Lister()
{
    delete _ui;
}
