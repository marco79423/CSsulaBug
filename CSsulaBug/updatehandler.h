#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H

#include <QObject>
#include <QHash>

class UpdateHandler : public QObject
{
    Q_OBJECT

public:

    explicit UpdateHandler(QObject *parent = 0);
    
signals:
    
    void updateInfo(const QHash<QString, QString> &info);
    void updateFinish();

public slots:

    virtual void update(){}
};

#endif // UPDATEHANDLER_H
