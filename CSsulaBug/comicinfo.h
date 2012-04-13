#ifndef COMICINFO_H
#define COMICINFO_H

#include <QString>
#include <QImage>

class ComicInfo
{
public:

    ComicInfo();
    QString getKey() const;
    QString getName() const;
    QString getType() const;
    QString getAuthor() const;
    QString getLastUpdated() const;
    QString getDescription() const;
    QImage getCover() const;

    void setKey(const QString &key);
    void setName(const QString &name);
    void setType(const QString &type);
    void setAuthor(const QString &author);
    void setLastUpdated(const QString &lastUpdated);
    void setDescription(const QString &description);
    void setCover(const QImage &cover);

    QString getInfo() const;

private:

    QString _key;
    QString _name;
    QString _type;
    QString _author;
    QString _lastUpdated;
    QString _description;
    QImage _cover;
};

#endif // COMICINFO_H
