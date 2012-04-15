#ifndef SFUPDATER_H
#define SFUPDATER_H

#include <QObject>
#include <QStringList>
#include <QMap>

#include "comicinfo.h"

class NetworkAccessor;

class SFUpdater : public QObject
{
    Q_OBJECT

public:

    enum State { Prepared, PageNumberGetting, ComicDataGetting};

    explicit SFUpdater(QObject *parent = 0);
    State getState() const;
    QList<ComicInfo> getComicList() const;
    int getComicCounts() const;

signals:

    void comicInfo(const ComicInfo &comicInfo);
    void finish();

public slots:
    
    void update();

private slots:

    void onOneReply(const QByteArray &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    State _state;
    int _comicCount;

    QList<ComicInfo> _comicInfoList;

    int getMaxPageNumber(const QString &content);
    QStringList getPageUrlList(const int &maxPageNumber);

    void initialize();
    void processComicData(const QString &content);
};

#endif // SFUPDATER_H
