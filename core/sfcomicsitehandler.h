#ifndef SFCOMICSITESERVICE_H
#define SFCOMICSITESERVICE_H

#include "acomicsitehandler.h"
#include "convertz.h"

#include <QNetworkRequest>
#include <QNetworkReply>

class NetworkAccessor;

class SFComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT

public:

    explicit SFComicSiteHandler(QObject *parent = 0);

    virtual QList<StringPair> getChapters(const QString &comicKey);
    virtual QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

public slots:

    virtual void updateComicInfos();

private slots:

    void _getComicInfo(const int id, QNetworkReply *reply);

private:

    NetworkAccessor *_networkAccessor;
    ConvertZ _convertz;

    QString _getHtmlFromNetwork(const QString &url);
    QNetworkRequest _makeRequest(const QString &url);
};

#endif // SFCOMICSITESERVICE_H
