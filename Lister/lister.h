#ifndef LISTER_H
#define LISTER_H

#include <QWidget>

class QSqlQueryModel;

namespace Ui {
class Lister;
}

class Lister : public QWidget
{
    Q_OBJECT
    
public:

    explicit Lister(QWidget *parent = 0);
    ~Lister();
    
private:

    Ui::Lister *_ui;
    QSqlQueryModel *_sqlQueryModel;
};

#endif // LISTER_H
