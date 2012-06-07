#-*- coding: cp950 -*-
from PyQt4 import QtCore, QtGui, uic

class MainView(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MainView, self).__init__(parent)
        uic.loadUi("MainView.ui", self)

