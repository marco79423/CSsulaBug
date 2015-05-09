#ifndef COMICINFOVIEW_H
#define COMICINFOVIEW_H

#include <QWidget>

namespace Ui {
class ComicInfoView;
}

class ComicInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit ComicInfoView(QWidget *parent = 0);

    void setComicName(QString comicName);

    ~ComicInfoView();

private:
    Ui::ComicInfoView *_ui;
};

#endif // COMICINFOVIEW_H
