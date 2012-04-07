#ifndef SFUPDATER_H
#define SFUPDATER_H

#include <QObject>

class NetworkAccessor;

class SFUpdater : public QObject
{
    Q_OBJECT

public:

    explicit SFUpdater(QObject *parent = 0);
    
signals:
    
    void finish();

public slots:
    

private:

    NetworkAccessor *_networkAccessor;
};

#endif // SFUPDATER_H
