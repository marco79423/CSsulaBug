#ifndef CORE_H
#define CORE_H

#include <QObject>

class ComicModel;
class DownloadHandler;

class Core : public QObject
{
    Q_OBJECT

public:

    explicit Core(QObject *parent = 0);
    ComicModel* model() const;
    
signals:
    
    void updateFinish();

public slots:

    void update();
    void download(const QString &key, const QString &dstDir);

private:

    ComicModel *_model;
    DownloadHandler *_downloadHandler;
};

#endif // CORE_H
