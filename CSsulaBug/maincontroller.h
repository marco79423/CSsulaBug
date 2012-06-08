#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QHash>

class UpdateHandler;
class DownloadHandler;

class MainController : public QObject
{
    Q_OBJECT

public:

    explicit MainController(QObject *parent = 0);
    
signals:
    
    void updateInfo(const QHash<QString, QString> &info);
    void updateFinish();

    void downloadInfo(const QHash<QString, QString> &info);
    void downloadFinish();

public slots:

    void setUpdateHandler(UpdateHandler *updateHandler);
    void setDownloadHandler(DownloadHandler *downloadHandler);

    void update();
    void download(const QString &name, const QString &dstDir);

private:

    UpdateHandler *_updateHandler;
    DownloadHandler *_downloadHandler;

    void _setConnection();
};

#endif // MAINCONTROLLER_H
