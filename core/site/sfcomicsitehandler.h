#ifndef SFCOMICSITESERVICE_H
#define SFCOMICSITESERVICE_H

#include "../acomicsitehandler.h"
#include "../convertz.h"

class QNetworkReply;

class NetworkAccessor;

class SFComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT

public:

    explicit SFComicSiteHandler(QObject *parent = 0);
    QString getComicSiteName() const;

    QList<StringPair> getChapters(const QString &comicKey);
    QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

public slots:

    void collectComicInfos();

private slots:

    void _onAccessorReply(QNetworkReply *reply);

private:

    NetworkAccessor *_networkAccessor;
    ConvertZ _convertz;
};

#endif // SFCOMICSITESERVICE_H
