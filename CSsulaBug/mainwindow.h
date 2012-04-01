#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HtmlDownloader;

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

    HtmlDownloader *_htmlDownloader;
};

#endif // MAINWINDOW_H
