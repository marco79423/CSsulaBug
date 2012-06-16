#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui
import handlers


class SiteModel(QtCore.QAbstractListModel):

    def __init__(self, parent=None):
        super(SiteModel, self).__init__(parent)

    def rowCount(self, parent=QtCore.QModelIndex()):
        pass

    def data(self, index, role):
        if not index.isValid():
            return None
        return data

    def headerData(section, orientation, role=Qt.DisplayRole):
        headerList = ["name", "site", "type", "author", "lastUpdated"]
        return headerList[section]
              
    def flags(self, index):
        pass

    def setData(self, index, value, role=EditRole):
        pass

    def appendRow(self):
        pass