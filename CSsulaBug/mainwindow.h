#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Form;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:

    Ui::MainWindow *_ui;
    Form *_form;
};

#endif // MAINWINDOW_H
