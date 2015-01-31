#ifndef BLCOMICSITEHANDLERTEST_H
#define BLCOMICSITEHANDLERTEST_H

#include <QObject>

class BLComicSiteHandlerTest : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase();
    void collectComicInfos();
    void getChapters();
    void getImageUrls();
};

#endif // BLCOMICSITEHANDLERTEST_H
