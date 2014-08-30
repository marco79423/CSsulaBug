#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>
#include <QPair>

#include <QHash>

typedef QPair<QString, QString> StringPair;
typedef QHash<QString, QString> StringHash;

Q_DECLARE_METATYPE(StringPair)
Q_DECLARE_METATYPE(StringHash)

#endif // GLOBALS_H
