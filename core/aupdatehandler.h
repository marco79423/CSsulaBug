#ifndef A_UPDATE_HANDLER_H
#define A_UPDATE_HANDLER_H

#include <QObject>
#include <QHash>

class AUpdateHandler : public QObject
{
    Q_OBJECT

public:

    typedef QHash<QString, QString> ComicInfo;

    virtual bool isReady() const { return true;}
    
signals:
    
    void info(const AUpdateHandler::ComicInfo &info);
    void finish();

public slots:

    virtual void update(){}

protected:

     explicit AUpdateHandler(QObject *parent = 0):QObject(parent){}
};

Q_DECLARE_METATYPE(AUpdateHandler::ComicInfo)

#endif // A_UPDATE_HANDLER_H
