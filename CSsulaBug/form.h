#ifndef FORM_H
#define FORM_H

#include <QWidget>

class QStandardItemModel;
class ComicInfo;
class SFUpdater;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:

    explicit Form(QWidget *parent = 0);

    ~Form();
    
private slots:

    void updateOneEntry(const ComicInfo& comicInfo);

private:

    Ui::Form *_ui;
    QStandardItemModel  *_model;
    SFUpdater *_updater;
};

#endif // FORM_H
