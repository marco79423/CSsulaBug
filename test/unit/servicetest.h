﻿#ifndef SERVICETEST_H
#define SERVICETEST_H

#include <QObject>

class AService;

class ServiceTest : public QObject
{
    Q_OBJECT

public:

    explicit ServiceTest(QObject *parent = 0);

private slots:

    void update();

private:

    AService *_service;
};

#endif // SERVICETEST_H