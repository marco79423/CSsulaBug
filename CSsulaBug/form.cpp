#include "form.h"
#include "ui_form.h"
#include "sfupdater.h"
#include "downloadcontroller.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QDataStream>
#include <QDebug>

Form::Form(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Form)
{
    //UI
    _ui->setupUi(this);
    _model = new QStandardItemModel(this);
    _model->setColumnCount(5);
    _model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Site"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Type"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Author"));
    _model->setHeaderData(4, Qt::Horizontal, tr("LastUpdated"));

    //Filter
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);
    _proxyModel->setDynamicSortFilter(true);

    connect(_ui->lineEdit, SIGNAL(textChanged(QString)),
            SLOT(setFilter(QString)));

    _ui->tableView->setModel(_proxyModel);

    connect(_ui->downloadButton, SIGNAL(clicked()), SLOT(download()));

    //Content
    _updater = new SFUpdater(this);

    connect(_updater, SIGNAL(comicInfo(const ComicInfo&)),
            SLOT(updateOneEntry(const ComicInfo&)));
    connect(_updater, SIGNAL(finish()), SLOT(done()));

    _downloadController = new DownloadController(this);
    connect(_downloadController, SIGNAL(message(const QString&))
            ,SIGNAL(message(const QString&)));
    connect(_downloadController, SIGNAL(finish()), SLOT(done()));

    //table
    QFile convertz(":/convertz.res");
    if(!convertz.open(QIODevice::ReadOnly))
    {
        qCritical() << "Form::can't open convertz" << convertz.errorString();
        getchar();
    }

    QTextStream in(&convertz);
    QString simplified = in.readLine();
    QString traditional = in.readLine();

    for(int i=0; i < simplified.size(); i++)
        _convertTable[simplified[i]] = traditional[i];
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
                         << (new QStandardItem(convertToTraditional(comicInfo.getName())))
                         << (new QStandardItem(convertToTraditional(comicInfo.getSite())))
                         << (new QStandardItem(convertToTraditional(comicInfo.getType())))
                         << (new QStandardItem(convertToTraditional(comicInfo.getAuthor())))
                         << (new QStandardItem(convertToTraditional(comicInfo.getLastUpdated())))
                      );
    _ui->tableView->resizeColumnsToContents();
}

void Form::setFilter(const QString &filter)
{
    QRegExp exp(filter, Qt::CaseInsensitive);
    _proxyModel->setFilterRegExp(exp);
}

QString Form::convertToTraditional(const QString &content)
{
    QString traditional;
    foreach(QChar word, content)
        traditional += _convertTable.value(word, word);
    return traditional;
}

void Form::done()
{
    if(_state == "Preparing")
        setState("Prepared");
    if(_state == "Downloading")
        setState("Prepared");
    _ui->downloadButton->setEnabled(true);
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

    _ui->downloadButton->setEnabled(false);

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
