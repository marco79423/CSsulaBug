#ifndef FILESAVER_H
#define FILESAVER_H

#include "afilesaver.h"

class FileSaver : public AFileSaver
{
    Q_OBJECT

public:

    FileSaver(QObject *parent = NULL);

    virtual SaverStatus saveFile(const QByteArray& data, const QString& filePath);

};

#endif // FILESAVER_H
