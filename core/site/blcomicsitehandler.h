#ifndef BLCOMICSITEHANDLER_H
#define BLCOMICSITEHANDLER_H

#include "../acomicsitehandler.h"
#include "../convertz.h"

class QNetworkReply;

class NetworkAccessor;

class BLComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT

public:

    explicit BLComicSiteHandler(QObject *parent = 0);
    QString getComicSiteName() const;

    QList<StringPair> getChapters(const QString &comicKey);
    QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

    virtual QString getReferer() const;

public slots:

    void collectComicInfos();

private slots:

    void _onAccessorReply(QNetworkReply* reply);

private:

    NetworkAccessor *_networkAccessor;
    ConvertZ _convertz;

    QString _getServerUrl(const int serverIndex);
};

#endif // BLCOMICSITEHANDLER_H
