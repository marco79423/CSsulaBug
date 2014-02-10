#include "core.h"
#include "sfdownloadhandler.h"
#include "comicmodel.h"

#include <QSortFilterProxyModel>
#include <QStandardPaths>
#include <QDebug>

Core::Core(QObject *parent) :
    QObject(parent)
{
    _model = new ComicModel(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_model);
    _downloadHandler = new SFDownloadHandler(this);

    connect(_model, SIGNAL(updateFinish()), SIGNAL(updateFinish()));
    connect(_downloadHandler, SIGNAL(finish()), SIGNAL(downloadFinish()));
    connect(_downloadHandler, SIGNAL(info(QHash<QString,QString>)), SLOT(_onGettingDownloadInfo(QHash<QString, QString>)));
}

QSortFilterProxyModel* Core::getModel() const
{
    return _proxyModel;
}

QString Core::getDownloadInfo() const
{
    return _downloadInfo;
}

void Core::update()
{
    _model->update();
}

void Core::download(const QString &key)
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    _downloadHandler->download(key, desktopPath);
}

void Core::setFilter(const QString &pattern)
{
    QString tpattern = _convertz.convertToTraditional(pattern);
    _proxyModel->setFilterRole(1);
    _proxyModel->setFilterRegExp(QRegExp(tpattern, Qt::CaseInsensitive, QRegExp::FixedString));
}

QString Core::getKey(const int index) const
{
    return _proxyModel->data(_proxyModel->index(index, 0), 2).toString();
}

void Core::_onGettingDownloadInfo(const QHash<QString, QString> &info)
{
    _downloadInfo = QString("[進度 %1%] 下載 %2").arg(info["progress"]).arg(info["path"]);
    qDebug() << "下載進度資訊" << _downloadInfo;
    emit downloadInfoChanged();
}




