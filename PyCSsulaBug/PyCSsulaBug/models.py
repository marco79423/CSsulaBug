#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import handlers

class ComicModel(QtCore.QAbstractListModel):

    def __init__(self, parent=None):
        super(ComicModel, self).__init__(parent)
        self._roles = dict(enumerate(["cover", "name", "site", "type", "author", "lastUpdated"]))
        self._comics = []
        self._siteHandler = handlers.SiteHandler(self)
        
        #initialize
        self.setRoleNames(self._roles)

        #SiteHandler
        self._siteHandler.setUpdateHandler(handlers.SFUpdateHandler())
        self._siteHandler.setDownloadHandler(handlers.SFDownloadHandler())

        self._setConnection()

    @QtCore.Slot()
    def update(self):
        self._siteHandler.update()

    def rowCount(self, parent = QtCore.QModelIndex()):
        return len(self._comics)
    
    def data(self, index, role=QtCore.Qt.DisplayRole):
        if index.row() < 0 or index.row() >= len(self._comics):
            return None 
        comic = self._comics[index.row()]
        
        infoType = []
        return comic[self._roles[role]]
        
    @QtCore.Slot()
    def _insertOneEntry(self, info):
        self.beginInsertRows(QtCore.QModelIndex(), self.rowCount(), self.rowCount())
        self._comics.append(info)
        self.endInsertRows()
    
    def _setConnection(self):
        self._siteHandler.updateInfo.connect(self._insertOneEntry)


"""
class SiteModel(QtCore.QObject):

    def __init__(self, parent=None):
        super(SiteModel, self).__init__(parent)
        self._model = QtGui.QStandardItemModel(self)
        self._proxyModel = QtGui.QSortFilterProxyModel(self)
        self._siteHandler = handlers.SiteHandler(self)

        self._model.setColumnCount(5);
        self._model.setHorizontalHeaderItem(0, QtGui.QStandardItem("Name"));
        self._model.setHorizontalHeaderItem(1, QtGui.QStandardItem("Site"));
        self._model.setHorizontalHeaderItem(2, QtGui.QStandardItem("Type"));
        self._model.setHorizontalHeaderItem(3, QtGui.QStandardItem("Author"));
        self._model.setHorizontalHeaderItem(4, QtGui.QStandardItem("LastUpdated"));

        #Filter
        self._proxyModel.setSourceModel(self._model);
        self._proxyModel.setDynamicSortFilter(True);

        #SiteHandler
        self._siteHandler.setUpdateHandler(handlers.SFUpdateHandler())
        self._siteHandler.setDownloadHandler(handlers.SFDownloadHandler())
        
        self._setConnection()
        
    @QtCore.Slot()
    def update(self):
        self._siteHandler.update()

    def model(self):
        return self._proxyModel

    def _setConnection(self):
        self._siteHandler.updateInfo.connect(self._insertOneEntry)
 
    @QtCore.Slot(dict)
    def _insertOneEntry(self, info):
        entry = []
        entry.append(QtGui.QStandardItem(info["name"]))
        entry.append(QtGui.QStandardItem(info["site"]))
        entry.append(QtGui.QStandardItem(info["type"]))
        entry.append(QtGui.QStandardItem(info["author"]))
        entry.append(QtGui.QStandardItem(info["lastUpdated"]))
        self._model.appendRow(entry)
"""    

if __name__ == "__main__":
    from PySide import QtGui
    import sys
    app = QtGui.QApplication(sys.argv)

    w = QtGui.QTableView()
    m = SiteModel()
    w.setModel(m)
    w.show()
    #m._insertOneEntry(dict(name="a", site="s", type="t", author="a", lastUpdated="l"))
    #m._insertOneEntry(dict(name="b", site="s", type="t", author="a", lastUpdated="l"))
        
    #w.update()
    
    
    sys.exit(app.exec_())