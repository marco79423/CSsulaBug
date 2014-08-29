#ifndef SFCOMICSITEHANDLERTEST_H
#define SFCOMICSITEHANDLERTEST_H

#include <QObject>

class SFComicSiteHandlerTest : public QObject
{
    Q_OBJECT

private slots:

    void update();
    void getChapters();
    void getImageUrls();
};

#endif // SFCOMICSITEHANDLERTEST_H
