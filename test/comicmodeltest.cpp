#include "comicmodeltest.h"
#include "fakedata.h"
#include <comicmodel.h>

#include <QTest>

void ComicModelTest::insertComicInfo()
{
    ComicModel *model = new ComicModel(this);
    FakeData fakeData;

    QVERIFY(model->rowCount() == 0);
    model->insertComicInfo(fakeData.getComicInfo(0));
    QVERIFY(model->rowCount() == 1);
    model->insertComicInfo(fakeData.getComicInfo(1));

    for(int i=0; i < 2; i++)
    {
        QVariantMap expected = fakeData.getComicInfo(0);
        QVariantMap actual = model->getComicInfo(0);

        QCOMPARE(actual["site"].toString(), expected["site"].toString());
        QCOMPARE(actual["coverUrl"].toString(), expected["coverUrl"].toString());
        QCOMPARE(actual["key"].toString(), expected["key"].toString());
        QCOMPARE(actual["name"].toString(), expected["name"].toString());
        QCOMPARE(actual["author"].toString(), expected["author"].toString());
        QCOMPARE(actual["type"].toString(), expected["type"].toString());
        QCOMPARE(actual["updateStatus"].toString(), expected["updateStatus"].toString());
    }
}

void ComicModelTest::updateComicInfo()
{
    ComicModel *model = new ComicModel(this);
    FakeData fakeData;
    QVariantMap comicInfo = fakeData.getComicInfo(0);
    QString comicKey = comicInfo["key"].toString();
    QString newName = "darkSite";
    model->insertComicInfo(comicInfo);
    QVERIFY(model->rowCount() == 1);
    comicInfo["name"] = "darkSite";
    model->updateComicInfo(comicInfo);
    QVERIFY(model->rowCount() == 1);
    QCOMPARE(newName, model->getComicInfo(0)["name"].toString());
}

void ComicModelTest::removeComicInfo()
{
    ComicModel *model = new ComicModel(this);
    FakeData fakeData;
    QVariantMap comicInfo = fakeData.getComicInfo(0);
    QString comicKey = comicInfo["key"].toString();
    QVERIFY(!model->hasComicInfo(comicKey));
    model->insertComicInfo(comicInfo);
    QVERIFY(model->hasComicInfo(comicKey));
    model->removeComicInfo(0);
    QVERIFY(!model->hasComicInfo(comicKey));
    model->insertComicInfo(comicInfo);
    QVERIFY(model->hasComicInfo(comicKey));
    model->removeComicInfo(comicKey);
    QVERIFY(!model->hasComicInfo(comicKey));

}
