#ifndef CONVERTZ_H
#define CONVERTZ_H

#include <QString>
#include <QHash>
#include <QChar>

class ConvertZ
{
public:

    ConvertZ();

    QString convertToTraditional(const QString &string);

private:

    QHash<QChar, QChar> _table;
};

#endif // CONVERTZ_H
