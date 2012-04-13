#include "comicinfo.h"

ComicInfo::ComicInfo()
{
}

QString ComicInfo::getKey() const
{
    return _key;
}

QString ComicInfo::getName() const
{
    return _name;
}

QString ComicInfo::getType() const
{
    return _type;
}

QString ComicInfo::getAuthor() const
{
    return _author;
}

QString ComicInfo::getLastUpdated() const
{
    return _lastUpdated;
}

QString ComicInfo::getDescription() const
{
    return _description;
}

QImage ComicInfo::getCover() const
{
    return _cover;
}

void ComicInfo::setKey(const QString &key)
{
    _key = key;
}

void ComicInfo::setName(const QString &name)
{
    _name = name;
}

void ComicInfo::setType(const QString &type)
{
    _type = type;
}

void ComicInfo::setAuthor(const QString &author)
{
    _author = author;
}

void ComicInfo::setLastUpdated(const QString &lastUpdated)
{
    _lastUpdated = lastUpdated;
}

void ComicInfo::setDescription(const QString &description)
{
    _description = description;
}

void ComicInfo::setCover(const QImage &cover)
{
    _cover = cover;
}

QString ComicInfo::getInfo() const
{
    return QString("key:%1, name:%2, type:%3, author:%4, lastUpdated:%5"
                   ",description:%6").arg(_key).arg(_name).arg(_type)
            .arg(_author).arg(_lastUpdated).arg(_description);
}
