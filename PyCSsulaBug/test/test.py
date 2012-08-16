#-*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative


class Animal:

    def __init__(self, type, size):
        self._type = type
        self._size = size

    def type(self):
        return self._type

    def size(self):
        return self._size

AnimalRoles = dict(enumerate(["TypeRole", "SizeRole"]))


class AnimalModel(QtCore.QAbstractListModel):

    AnimalRoles = dict(TypeRole=QtCore.Qt.UserRole + 1,
                       SizeRole=QtCore.Qt.UserRole + 2)
        
    def __init__(self, parent=None):
        super(AnimalModel, self).__init__(parent)
        self._animals = []
        roles = dict()
        roles[AnimalModel.AnimalRoles["TypeRole"]] = "type"
        roles[AnimalModel.AnimalRoles["SizeRole"]] = "size"
        self.setRoleNames(roles)

    def addAnimal(self, animal):
        self.beginInsertRows(QtCore.QModelIndex(), self.rowCount(), self.rowCount())
        self._animals.append(animal)
        self.endInsertRows()

    def rowCount(self, parent = QtCore.QModelIndex()):
        return len(self._animals)
    
    def data(self, index, role=QtCore.Qt.DisplayRole):
        if index.row() < 0 or index.row() > len(self._animals):
            return None 
        animal = self._animals[index.row()]
        if role == AnimalModel.AnimalRoles["TypeRole"]:
            return animal.type()
        elif role == AnimalModel.AnimalRoles["SizeRole"]:
            return animal.size()
        return None
     
   
import sys
app = QtGui.QApplication(sys.argv)

codec = QtCore.QTextCodec.codecForName("utf-8")
QtCore.QTextCodec.setCodecForCStrings(codec)
QtCore.QTextCodec.setCodecForTr(codec)
QtCore.QTextCodec.setCodecForLocale(codec)

model = AnimalModel() 
model.addAnimal(Animal("Wolf", "Medium"))
model.addAnimal(Animal("Polar bear", "Large"))
model.addAnimal(Animal("Quoll", "Small"))

view = QtDeclarative.QDeclarativeView()
ctx = view.rootContext()    
ctx.setContextProperty('myModel', model)
view.setSource(QtCore.QUrl("test.qml"))
view.show()

sys.exit(app.exec_())