#include "comicinfoview.h"
#include "ui_comicinfoview.h"

ComicInfoView::ComicInfoView(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ComicInfoView)
{
    _ui->setupUi(this);
}

void ComicInfoView::setComicName(QString comicName)
{
    _ui->comicNameLabel->setText(comicName);
}

ComicInfoView::~ComicInfoView()
{
    delete _ui;
}
