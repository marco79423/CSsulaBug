#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import handlers

class ComicModel(QtCore.QAbstractListModel):

    updateInfo = QtCore.Signal(dict)
    updateFinish = QtCore.Signal()

    def __init__(self, parent=None):
        super(ComicModel, self).__init__(parent)
        self._roles = dict(enumerate(["cover", "name", "key", "site", "type", "author", "lastUpdated"]))
        self._comics = []
        self._updateHandler = handlers.SFUpdateHandler(self)
        
        #initialize
        self.setRoleNames(self._roles)
        self._setConnection()

    @QtCore.Slot()
    def update(self):
        self._updateHandler.update()

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
        self._updateHandler.updateInfo.connect(self._insertOneEntry)
        self._updateHandler.updateInfo.connect(self.updateInfo)
        self._updateHandler.updateFinish.connect(self.updateFinish)

if __name__ == "__main__":
    from PySide import QtGui
    import sys
    app = QtGui.QApplication(sys.argv)
    
    
    sys.exit(app.exec_())