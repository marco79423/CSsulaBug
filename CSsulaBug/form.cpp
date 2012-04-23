#include "form.h"
#include "ui_form.h"
#include "sfupdater.h"
#include <QStandardItemModel>

Form::Form(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Form)
{
    _ui->setupUi(this);
    _model = new QStandardItemModel(this);
    _model->setColumnCount(5);
    _model->setHeaderData(0, Qt::Horizontal, tr("Site"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Type"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Author"));
    _model->setHeaderData(4, Qt::Horizontal, tr("LastUpdated"));

    _ui->tableView->setModel(_model);
    _ui->tableView->setSelectionBehavior(QTableView::SelectRows);
    _ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    _updater = new SFUpdater(this);
    connect(_updater, SIGNAL(comicInfo(const ComicInfo&)),
            SLOT(updateOneEntry(const ComicInfo&)));
    _updater->update();
}

Form::~Form()
{
    delete _ui;
}

void Form::updateOneEntry(const ComicInfo &comicInfo)
{
    _model->appendRow(QList<QStandardItem*>()
                         << (new QStandardItem(comicInfo.getSite()))
                         << (new QStandardItem(comicInfo.getName()))
                         << (new QStandardItem(comicInfo.getType()))
                         << (new QStandardItem(comicInfo.getAuthor()))
                         << (new QStandardItem(comicInfo.getLastUpdated()))
                      );
    _ui->tableView->resizeColumnsToContents();
}
