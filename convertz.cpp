#include "convertz.h"
#include <QFile>
#include <QDebug>

ConvertZ::ConvertZ()
{
    QFile file(":/convertz.dat");
    if(!file.open(QIODevice::ReadOnly))
        qCritical() << "無法開啟 convertz.dat";

    QDataStream in(&file);
    in >> _table;
    file.close();
}

QString ConvertZ::convertToTraditional(const QString &string)
{
    QString tString;
    foreach(QChar word, string)
        tString += _table.value(word, word);
    return tString;
}
