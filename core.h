#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <convertz.h>

class QSortFilterProxyModel;

class ComicModel;
class DownloadHandler;

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString downloadInfo READ getDownloadInfo NOTIFY downloadInfoChanged)
public:

    explicit Core(QObject *parent = 0);
    QSortFilterProxyModel* model() const;
    QString getDownloadInfo() const;

signals:
    
    void updateFinish();
    void downloadFinish();
    void downloadInfoChanged();

public slots:

    void update();
    void download(const QString &key, const QString &dstDir);
    void setFilter(const QString &pattern);
    QString getKey(const int index) const;

    void _onGettingDownloadInfo(const QHash<QString, QString> &info);
private:
    ComicModel *_model;
    QSortFilterProxyModel *_proxyModel;
    DownloadHandler *_downloadHandler;
    ConvertZ _convertz;

    QString _downloadInfo;
};

#endif // CORE_H
