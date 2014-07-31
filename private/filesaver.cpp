#include "filesaver.h"

#include <QFileInfo>
#include <QDir>

FileSaver::FileSaver(QObject *parent)
    :AFileSaver(parent)
{
}


void FileSaver::onSaveFile(const int &id, const QByteArray &data, const QString &filePath)
{
    //檢查目標檔案是否存在
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists())
    {
        emit finish(id, SaverStatus::FileExists);
        return;
    }

    //檢查對應的資料夾是否存在，若不存在則建立
    QDir dir = fileInfo.absoluteDir();
    if(!dir.exists() && !dir.mkpath(dir.absolutePath()))
    {
        emit finish(id, SaverStatus::FailedToCreateDstDir);
        return;
    }

    //檢查是可以開啟目標檔案
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        emit finish(id, SaverStatus::FailedToCreateDstFile);
        return;
    }

    //寫入檔案
    if(file.write(data) == -1)
    {
        emit finish(id, SaverStatus::FailedToWriteDstFile);
        return;
    }
    file.close();

    emit finish(id, SaverStatus::Success);
}
