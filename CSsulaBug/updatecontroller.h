#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

#include <QObject>

class SFUpdater;
class SFCoverUpdater;

class ComicDatabase;

class UpdateController : public QObject
{
    Q_OBJECT

public:

    enum State {Prepared, GettingComic, GettingCover};

    explicit UpdateController(QObject *parent = 0);
    
signals:
    
    void finish();

public slots:
    
    void update();

private slots:

    void processComic();
    void processCover();

private:

    State _state;

    SFUpdater *_updater;
    SFCoverUpdater *_coverUpdater;

    ComicDatabase *_comicDatabase;
};

#endif // UPDATECONTROLLER_H
