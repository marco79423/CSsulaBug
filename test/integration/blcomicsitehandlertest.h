#ifndef BLCOMICSITEHANDLERTEST_H
#define BLCOMICSITEHANDLERTEST_H

#include <QObject>

class BLComicSiteHandlerTest : public QObject
{
    Q_OBJECT

private slots:

    void update();
    void getChapters();
    void getImageUrls();
};

#endif // BLCOMICSITEHANDLERTEST_H
