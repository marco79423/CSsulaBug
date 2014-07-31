﻿#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QHash>
#include <QStringList>

#include "afilesaver.h"

class NetworkAccessor;
class QNetworkReply;

class Downloader : public QObject
{
    Q_OBJECT

public:

    //Task => (Url, FilePath)
    typedef QHash<QString, QString> Task;

    explicit Downloader(AFileSaver *fileSaver, QObject *parent = 0);

signals:
    
    void info(const QHash<QString, QString> &downloadInfo);
    void finish();

public slots:

    int download(const Task &task);

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id);

private:

    AFileSaver *_fileSaver;

    NetworkAccessor *_networkAccessor;
    QHash<int, Task> _taskHash;
};

#endif // DOWNLOADER_H
