#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "htmldownloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _htmlDownloader = new HtmlDownloader(this);
    //_htmlDownloader->request("http://comic.sfacg.com/Catalog/");
    _htmlDownloader->request("http://hotpic.sfacg.com/Pic/OnlineComic2/XFGJ/354/001_4051.png");
}

MainWindow::~MainWindow()
{
    delete _ui;
}
