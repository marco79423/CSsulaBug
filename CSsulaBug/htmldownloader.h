#ifndef HTMLDOWNLOADER_H
#define HTMLDOWNLOADER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class HtmlDownloader : public QObject
{
    Q_OBJECT

public:

    explicit HtmlDownloader(QObject *parent = 0);
    
    void request(const QString &url);

signals:
    
public slots:

    void done(QNetworkReply *reply);

private:
    
    QNetworkAccessManager *_networkManager;
};

#endif // HTMLDOWNLOADER_H
