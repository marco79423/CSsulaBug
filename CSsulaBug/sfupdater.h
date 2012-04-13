#ifndef SFUPDATER_H
#define SFUPDATER_H

#include <QObject>
#include <QStringList>
#include <QHash>

class NetworkAccessor;

class SFUpdater : public QObject
{
    Q_OBJECT

public:

    enum State { Prepared, PageNumberGetting, ComicDataGetting };
    explicit SFUpdater(QObject *parent = 0);
    State getState() const;
    QList<QHash<QString, QString> > getComicList() const;
    int getCounts() const;

signals:

    void comicInfo(const QHash<QString, QString> &comicInfo);
    void count(const int& count);
    void finish();

public slots:
    
    void update();

private slots:

    void onOneReply(const QString &content);
    void onReplyFinish();

private:

    NetworkAccessor *_networkAccessor;
    State _state;
    int _count;
    QList<QHash<QString, QString> > _comicInfoList;

    int getMaxPageNumber(const QString &content);
    QStringList getPageUrlList(const int &maxPageNumber);

    void initialize();
    void processComicData(const QString &content);
};

#endif // SFUPDATER_H
