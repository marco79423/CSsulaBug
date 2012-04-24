#include "downloadcontroller.h"
#include "sfdownloadpreparer.h"
#include "networkaccessor.h"
#include <QDir>
#include <QDebug>

DownloadController::DownloadController(QObject *parent)
    :QObject(parent)
{
    _networkAccessor = new NetworkAccessor(this);
    connect(_networkAccessor,
            SIGNAL(oneReply(const QString&, const QByteArray&)),
            SLOT(onOneReply(const QString&, const QByteArray&)));

    connect(_networkAccessor, SIGNAL(finish()), SLOT(onReplyFinish()));

    _downloadPreparer = new SFDownloadPreparer(this);
    connect(_downloadPreparer, SIGNAL(finish()), SLOT(downloadImages()));
}


void DownloadController::download(const QString &key, const QString &name)
{
    _comicName = name;
    _downloadPreparer->prepare(key);
}

void DownloadController::downloadImages()
{
    qDebug() << "DownloaderController::downloadImages start ...";

    QStringList chapterList = _downloadPreparer->getChapterNameList();
    foreach(QString chapterName, chapterList)
    {
        QString dirPath = _comicName + "/" + chapterName;

        if(!QDir(dirPath).exists())
        {
            if(!QDir().mkpath(dirPath))
                qCritical() << "DownloaderController:: can't make dir "
                            << dirPath;
        }

        QStringList imageList = _downloadPreparer->getUrlList(chapterName);
        for(int i = 0; i < imageList.count(); i++)
        {
            QString filePath = QString("%1/%2.%3")
                    .arg(dirPath).arg(i, 3, 10, QChar('0'))
                    .arg(imageList[i].right(3));

            if(!QFile(filePath).exists())
                _downloadHash[imageList[i]] = filePath;
            else
                imageList.removeAll(imageList[i]);
        }

        _networkAccessor->get(imageList);
    }
}

void DownloadController::onOneReply(const QString& url,
                                      const QByteArray& content)
{
    QString filePath = _downloadHash[url];

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        qCritical() << "DownloaderController::open　" << filePath << "failed";
        return;
    }

    file.write(content);
    file.close();

    qDebug() << "DownloaderController:: downloaded " << filePath;
    _downloadHash.remove(url);
}

void DownloadController::onReplyFinish()
{
    if(_downloadHash.empty())
        emit finish();
}


