#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>

class Delegate : public QItemDelegate
{
    Q_OBJECT

public:

    explicit Delegate(QObject * parent = 0);
    
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;

signals:
    
public slots:
    
};

#endif // DELEGATE_H
