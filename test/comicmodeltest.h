﻿#ifndef COMICMODELTEST_H
#define COMICMODELTEST_H

#include <QObject>

class ComicModelTest : public QObject
{
    Q_OBJECT

private slots:

    void insertComicInfo();
    void updateComicInfo();
    void removeComicInfo();

};

#endif // COMICMODELTEST_H
