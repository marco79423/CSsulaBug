#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include "downloader.h"

class ImageDownloader : public Downloader
{
    Q_OBJECT

public:

    explicit ImageDownloader(QObject *parent = 0);
    
public slots:
    
    void done(QNetworkReply *reply);
};

#endif // IMAGEDOWNLOADER_H
