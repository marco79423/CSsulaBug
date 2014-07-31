#include "afilesaver.h"

int AFileSaver::saveFile(const QByteArray &data, const QString &filePath)
{
    emit startSaveFile(_id, data, filePath);
    return _id++;
}

AFileSaver::AFileSaver(QObject *parent)
    :QObject(parent), _id(0)
{
    connect(this, SIGNAL(startSaveFile(const int&, const QByteArray&, const QString&)),
            SLOT(onSaveFile(const int&, const QByteArray&, const QString&)), Qt::QueuedConnection);
}
