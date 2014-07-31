#ifndef AFILESAVER_H
#define AFILESAVER_H

#include <QObject>
#include <QByteArray>

class AFileSaver : public QObject
{
    Q_OBJECT

public:

    enum class SaverStatus
    {
        Success,
        FileExists,
        FailedToCreateDstDir,
        FailedToCreateDstFile,
        FailedToWriteDstFile
    };

    virtual SaverStatus saveFile(const QByteArray& data, const QString& filePath) = 0;

protected:

    explicit AFileSaver(QObject *parent = 0): QObject(parent) {}

};

#endif // AFILESAVER_H
