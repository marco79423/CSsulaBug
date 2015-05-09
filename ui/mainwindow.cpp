#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comicinfodelegate.h"
#include <aservice.h>

MainWindow::MainWindow(AService *service, QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _service(service)
{
    _ui->setupUi(this);
    _ui->comicListView->setItemDelegate(new ComicInfoDelegate(this));
    _ui->comicListView->setGridSize(QSize(400, 130));
    _ui->comicListView->setModel(_service->getProxyComicModel());

    _service->setParent(this);
    _service->collectComicInfos();
}

MainWindow::~MainWindow()
{
    delete _ui;
}
