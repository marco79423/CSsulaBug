#ifndef SFDOWNLOADPREPARER_H
#define SFDOWNLOADPREPARER_H

#include <QObject>
#include <QStringList>
#include <QHash>

class QNetworkAccessManager;
class QNetworkReply;

class SFDownloadPreparer
    :public QObject
{
    Q_OBJECT

public:

    enum State { Prepared, ChapterNameListing, UrlListing};

    explicit SFDownloadPreparer(QObject *parent = 0);
    
    QStringList getChapterNameList();
    QStringList getUrlList(const QString &chapterName);

signals:
    
    void finish();

public slots:
    
    void prepare(const QString &key);

private slots:

    void onReply(QNetworkReply *reply);

private:

    QNetworkAccessManager *_networkAccessManager;

    State _state;

    QStringList _chapterNameList;
    int _comicID;
    QString _comicType;

    QHash<QString, QStringList> _urlListHash;

    QStringList _checkList;

    void initialize();
    void listChapterName(const QString &content);
    void prepareListingUrl();
    void listUrl(const QString &chapterName, const QString &content);
};

#endif // SFDOWNLOADPREPARER_H
