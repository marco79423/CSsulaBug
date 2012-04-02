#include "downloadercontroller.h"
#include "sfdownloadpreparer.h"
#include <QtNetwork>
#include <QDir>
#include <QDebug>

DownloaderController::DownloaderController(QObject *parent) :
    QObject(parent)
{
    _networkAccessManager = new QNetworkAccessManager(this);
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onReply(QNetworkReply*)));

    _downloadPreparer = new SFDownloadPreparer(this);
    connect(_downloadPreparer, SIGNAL(finish()), SLOT(listDownloadList()));
}

void DownloaderController::download(const QString &key,
                                    const QString &dirPath)
{
    _comicName = key;
    _dirPath = dirPath;
    _downloadPreparer->prepare(key);
}

void DownloaderController::listDownloadList()
{
    qDebug() << "DownloaderController::　開始　listDownloadList";
    QStringList chapterList = _downloadPreparer->getChapterNameList();
    foreach(QString chapterName, chapterList)
    {
        QString dirPath = _dirPath + "/" + _comicName + "/" + chapterName;

        QDir dir;
        if(!dir.mkpath(dirPath))
            qCritical() << "DownloaderController:: 無法建立　" << dirPath;


        QStringList imageList = _downloadPreparer->getUrlList(chapterName);
        for(int i = 0; i < imageList.count(); i++)
        {
            QString filePath = QString("%1/%2.%3")
                    .arg(dirPath).arg(i, 3, 10, QChar('0'))
                    .arg(imageList[i].right(3));

            QFile file(filePath);
            if(!file.exists())
            {
                _downloadHash[imageList[i]] = filePath;
                qDebug() << "DownloaderController:: 設定對應　"
                        << imageList[i] << filePath;

                get(imageList[i]);
            }
        }
    }
}

void DownloaderController::get(const QString &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                     "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                     "1084.1 Safari/536.5");
    _networkAccessManager->get(request);
}

void DownloaderController::onReply(QNetworkReply *reply)
{
    if(reply->error())
    {
        qCritical() << tr("DownloaderController:: error") << reply->error();
        reply->deleteLater();
        return;
    }

    QString url = reply->url().toString();
    QString filePath = _downloadHash[url];

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        qCritical() << "DownloaderController::　開啟　" << filePath << "失敗";
        return;
    }

    file.write(reply->readAll());
    file.close();

    qDebug() << "DownloaderController:: 下載完 " << filePath;
    _downloadHash.remove(url);
    if(_downloadHash.empty())
        emit finish();

}
