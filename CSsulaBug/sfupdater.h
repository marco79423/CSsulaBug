#ifndef SFUPDATER_H
#define SFUPDATER_H

#include <QObject>
#include <QStringList>

class NetworkAccessor;

class SFUpdater : public QObject
{
    Q_OBJECT

public:

    enum State { Prepared, PageNumberGetting, ComicDataGetting };
    explicit SFUpdater(QObject *parent = 0);
    State getState() const;

signals:
    
    void finish();

public slots:
    
    void update();

private slots:

    void onOneReply(const QString &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    State _state;

    int getMaxPageNumber(const QString &content);
    QStringList getPageUrlList(const int &maxPageNumber);

    void processComicData(const QString &content);
};

#endif // SFUPDATER_H
