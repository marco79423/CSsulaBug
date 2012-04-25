#include "form.h"
#include "ui_form.h"
#include "sfupdater.h"
#include "downloadcontroller.h"
#include <QStandardItemModel>
#include <QDebug>

Form::Form(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Form)
{
    _ui->setupUi(this);
    _model = new QStandardItemModel(this);
    _model->setColumnCount(5);
    _model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Site"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Type"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Author"));
    _model->setHeaderData(4, Qt::Horizontal, tr("LastUpdated"));

    _ui->tableView->setModel(_model);
    _ui->tableView->setSelectionBehavior(QTableView::SelectRows);
    _ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    connect(_ui->downloadButton, SIGNAL(clicked()), SLOT(download()));

    _updater = new SFUpdater(this);

    connect(_updater, SIGNAL(comicInfo(const ComicInfo&)),
            SLOT(updateOneEntry(const ComicInfo&)));
    connect(_updater, SIGNAL(finish()), SLOT(done()));

    _downloadController = new DownloadController(this);
    connect(_downloadController, SIGNAL(message(const QString&))
            ,SIGNAL(message(const QString&)));
    connect(_downloadController, SIGNAL(finish()), SLOT(done()));
}

Form::~Form()
{
    delete _ui;
}

void Form::setState(const QString &state)
{
    if(_state != state)
    {
        qDebug() << "Form:: state change to " << state;
        _state = state;
        emit stateChanged(state);
    }
}

void Form::updateOneEntry(const ComicInfo &comicInfo)
{
    _model->appendRow(QList<QStandardItem*>()
                         << (new QStandardItem(comicInfo.getName()))
                         << (new QStandardItem(comicInfo.getSite()))
                         << (new QStandardItem(comicInfo.getType()))
                         << (new QStandardItem(comicInfo.getAuthor()))
                         << (new QStandardItem(comicInfo.getLastUpdated()))
                      );
    _ui->tableView->resizeColumnsToContents();
}

void Form::done()
{
    if(_state == "Preparing")
        setState("Prepared");
    if(_state == "Downloading")
        setState("Prepared");
}

void Form::update()
{
    setState("Preparing");
    _updater->update();
}

void Form::download()
{
    if(_state != "Prepared")
    {
        qCritical() << "Form::isn't Prepared";
        return;
    }

    setState("Downloading");

    QModelIndex index = _ui->tableView->selectionModel()->
                            selection().indexes()[0];

    QString name = _model->data(index).toString();
    qDebug() << "Form:: prepared to download " << name;

    QString key;
    QList<ComicInfo> comicInfoList = _updater->getComicList();
    foreach(ComicInfo info, comicInfoList)
    {
        if(info.getName() == name)
        {
            key = info.getKey();
            break;
        }
    }
    qDebug() << "Form:: get key " << key;
    _downloadController->download(key, name);
}
