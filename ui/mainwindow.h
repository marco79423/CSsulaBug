#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class AService;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AService *service, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    AService *_service;
};

#endif // MAINWINDOW_H
