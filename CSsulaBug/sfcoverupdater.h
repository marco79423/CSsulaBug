#ifndef SFCOVERUPDATER_H
#define SFCOVERUPDATER_H

#include <QObject>
#include <QMap>

#include "comicinfo.h"

class NetworkAccessor;

class SFCoverUpdater : public QObject
{
    Q_OBJECT

public:

    enum State { Prepared, CoverImageGetting};

    explicit SFCoverUpdater(QObject *parent = 0);
    State getState() const;
    QList<ComicInfo> getComicList() const;
    int getCoverCounts() const;

signals:
    
    void comicInfo(const ComicInfo &comicInfo);
    void finish();

public slots:
    
    void update(const QList<ComicInfo> &comicInfoList);

private slots:

    void onOneReply(const QString &url, const QByteArray &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    State _state;
    int _coverCount;

    QList<ComicInfo> _comicInfoList;
    QMap<QString, int> _coverMap;

    void initialize();
    void processCoverImageData(const QString &url, const QByteArray &content);

};

#endif // SFCOVERUPDATER_H
