#ifndef NETWORKACCESSOR_H
#define NETWORKACCESSOR_H

#include <QObject>
#include <QStringList>
#include <QHash>

class QNetworkAccessManager;
class QNetworkReply;

class NetworkAccessor : public QObject
{
    Q_OBJECT

public:

    explicit NetworkAccessor(QObject *parent = 0);
    
    void get(const QString &url);
    void get(const QStringList &urlList);

signals:
    
    void oneReply(const QString &url, const QByteArray &content);
    void oneReply(const QByteArray &content);
    void finish();

private slots:

    void onReply(QNetworkReply *reply);

private:

    QNetworkAccessManager *_networkAccessManager;
    QList<QString> _checkList;
    
};

#endif // NETWORKACCESSOR_H
