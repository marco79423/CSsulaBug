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

    enum State { Prepared, PageNumberGetting,
                 ComicDataGetting, CoverImageGetting};

    explicit SFUpdater(QObject *parent = 0);
    State getState() const;
    QList<ComicInfo> getComicList() const;
    int getComicCounts() const;
    int getCoverCounts() const;

signals:

    void comicInfo(const ComicInfo &comicInfo);
    void finish();

public slots:
    
    void update();

private slots:

    void onOneReply(const QString &url, const QByteArray &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    State _state;
    int _comicCount;
    int _coverCount;

    QList<ComicInfo> _comicInfoList;
    QMap<QString, int> _imageMap;

    int getMaxPageNumber(const QString &content);
    QStringList getPageUrlList(const int &maxPageNumber);

    void initialize();
    void processComicData(const QByteArray &content);
    void processCoverImage(const QString &url, const QByteArray &content);
};

#endif // SFUPDATER_H
