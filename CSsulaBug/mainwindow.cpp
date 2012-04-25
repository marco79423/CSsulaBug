#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _form = new Form(this);
    setCentralWidget(_form);
    connect(_form, SIGNAL(stateChanged(const QString&)),
            _ui->statusbar, SLOT(showMessage(const QString&)));
    connect(_form, SIGNAL(message(const QString&)),
            _ui->statusbar, SLOT(showMessage(const QString&)));

    _form->update();
}

MainWindow::~MainWindow()
{
    delete _ui;
}
