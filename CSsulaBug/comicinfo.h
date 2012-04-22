#ifndef COMICINFO_H
#define COMICINFO_H

#include <QString>
#include <QImage>

class ComicInfo
{
public:

    ComicInfo();
    QString getSite() const;
    QString getKey() const;
    QString getName() const;
    QString getType() const;
    QString getAuthor() const;
    QString getLastUpdated() const;
    QString getDescription() const;
    QString getCoverUrl() const;
    QImage getCover() const;

    void setSite(const QString &site);
    void setKey(const QString &key);
    void setName(const QString &name);
    void setType(const QString &type);
    void setAuthor(const QString &author);
    void setLastUpdated(const QString &lastUpdated);
    void setDescription(const QString &description);
    void setCoverUrl(const QString &url);
    void setCover(const QImage &cover);

    QString getInfo() const;

    bool hasCover() const;

private:

    QString _site;
    QString _key;
    QString _name;
    QString _type;
    QString _author;
    QString _lastUpdated;
    QString _description;
    QString _coverUrl;
    QImage _cover;

    bool _hasCover;
};

#endif // COMICINFO_H
