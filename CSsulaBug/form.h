#ifndef FORM_H
#define FORM_H

#include <QWidget>

class QStandardItemModel;
class QSortFilterProxyModel;
class ComicInfo;
class SFUpdater;
class DownloadController;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:

    explicit Form(QWidget *parent = 0);

    ~Form();
    
signals:

    void stateChanged(const QString &state);
    void message(const QString &state);

public slots:

    void update();
    void download();

private slots:

    void setState(const QString &state);
    void updateOneEntry(const ComicInfo& comicInfo);
    void setFilter(const QString& filter);
    void done();

private:

    Ui::Form *_ui;

    QString _state;
    QStandardItemModel  *_model;
    QSortFilterProxyModel *_proxyModel;
    SFUpdater *_updater;
    DownloadController *_downloadController;
};

#endif // FORM_H
