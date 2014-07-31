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

    virtual int saveFile(const QByteArray& data, const QString& filePath);

signals:

    void startSaveFile(const int& id, const QByteArray& data, const QString& filePath);
    void finish(const int& id, const AFileSaver::SaverStatus& saverStatus);

protected:

    explicit AFileSaver(QObject *parent = 0);

protected slots:

    virtual void onSaveFile(const int& id, const QByteArray& data, const QString& filePath){}

private:

    int _id;
};

Q_DECLARE_METATYPE(AFileSaver::SaverStatus)

#endif // AFILESAVER_H
