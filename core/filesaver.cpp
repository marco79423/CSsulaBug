#include "filesaver.h"

#include <QFileInfo>
#include <QDir>


FileSaver::FileSaver(QObject *parent)
    :AFileSaver(parent)
{

}


AFileSaver::SaverStatus FileSaver::saveFile(const QByteArray &data, const QString &filePath)
{
    //檢查目標檔案是否存在
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists())
    {
        return FileExists;
    }

    //檢查對應的資料夾是否存在，若不存在則建立
    QDir dir = fileInfo.absoluteDir();
    if(!dir.exists() && !dir.mkpath(dir.absolutePath()))
    {
        return FailedToCreateDstDir;
    }

    //檢查是可以開啟目標檔案
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        return FailedToCreateDstFile;
    }

    //寫入檔案
    if(file.write(data) == -1)
    {
        return FailedToWriteDstFile;
    }
    file.close();

    return Success;
}

