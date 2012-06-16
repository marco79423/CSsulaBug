#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import views
import handlers

class MainWindow(QtGui.QMainWindow):
    
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self._mainView = views.MainView(self)

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
        self._siteHandler.updateInfo.connect(self._insertOneEntry)

        #初始設定
        self.setCentralWidget(self._mainView)
        self._mainView.ui.tableView.setModel(self._proxyModel)
        self._setConnection()

        self._siteHandler.update()
            
        
    def _setConnection(self):
        pass

    @QtCore.Slot(dict)
    def _insertOneEntry(self, info):
        entry = []
        entry.append(QtGui.QStandardItem(info["name"]))
        entry.append(QtGui.QStandardItem(info["site"]))
        entry.append(QtGui.QStandardItem(info["type"]))
        entry.append(QtGui.QStandardItem(info["author"]))
        entry.append(QtGui.QStandardItem(info["lastUpdated"]))

        self._model.appendRow(entry)



if __name__ in "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)

    codec = QtCore.QTextCodec.codecForName("utf-8")
    QtCore.QTextCodec.setCodecForCStrings(codec)
    QtCore.QTextCodec.setCodecForTr(codec)
    QtCore.QTextCodec.setCodecForLocale(codec)

    m = MainWindow()
    m.show()
    sys.exit(app.exec_())