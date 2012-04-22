#include "comicinfo.h"

ComicInfo::ComicInfo()
    :_hasCover(false)
{
}

QString ComicInfo::getSite() const
{
    return _site;
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

QString ComicInfo::getCoverUrl() const
{
    return _coverUrl;
}

QImage ComicInfo::getCover() const
{
    return _cover;
}

void ComicInfo::setSite(const QString &site)
{
    _site = site;
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

void ComicInfo::setCoverUrl(const QString &url)
{
    _coverUrl = url;
}

void ComicInfo::setCover(const QImage &cover)
{
    if(!cover.isNull())
    {
        _hasCover = true;
        _cover = cover;
    }
}

QString ComicInfo::getInfo() const
{
    return QString("site: %1, key:%2, name:%3, type:%4, author:%5,"
                   "lastUpdated:%6, description:%7, coverUrl: %8")
            .arg(_site).arg(_key).arg(_name).arg(_type).arg(_author)
            .arg(_lastUpdated).arg(_description).arg(_coverUrl);
}

bool ComicInfo::hasCover() const
{
    return _hasCover;
}
