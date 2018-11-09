from PyQt5.QtCore import Qt
from PyQt5.QtSql import QSqlQueryModel, QSqlQuery
from PyQt5.QtWidgets import *

from connection import createConnection


class Scene(QWidget):
    def __init__(self, title, query, parent=None):
        QWidget.__init__(self, parent)
        self.q = query
        self.setLayout(QVBoxLayout())
        titleLabel = QLabel(title, self)
        self.layout().addWidget(titleLabel)
        titleLabel.setAlignment(Qt.AlignHCenter)

        self.listView = QListView(self)
        self.model = QSqlQueryModel(self)
        self.listView.setModel(self.model)
        self.layout().addWidget(self.listView)

    def setQuery(self, q):
        self.q = q
        self.updateModel()

    def updateModel(self):
        self.model.setQuery(self.q)
        self.listView.setModelColumn(1)


class NotInScene(Scene):
    def __init__(self, id, parent=None):
        self.fm = "SELECT * FROM Character WHERE characterID NOT IN " \
                 "(SELECT characterID FROM CharacterInScene WHERE sceneID={})"
        Scene.__init__(self, "Not in Scene", self.fm.format(id), parent)
        self.updateModel()

    def setSceneId(self, id):
        self.setQuery(self.fm.format(id))


class InScene(Scene):
    def __init__(self, id, parent=None):
        self.fm = "SELECT * FROM Character WHERE characterID IN "" \
        ""(SELECT characterID FROM CharacterInScene WHERE sceneID={})"
        Scene.__init__(self, "In Scene", self.fm.format(id), parent)

    def setSceneId(self, id):
        self.setQuery(self.fm.format(id))


class SceneWidget(QWidget):
    def __init__(self, sceneId, parent=None):
        QWidget.__init__(self, parent)
        self.setLayout(QHBoxLayout())

        self.sceneId = sceneId

        self.notInScene = NotInScene(1, self)
        self.layout().addWidget(self.notInScene)

        vLayout2 = QVBoxLayout()
        vLayout2.addItem(QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding))
        self.addButton = QToolButton(self)
        self.addButton.setText(">")
        self.addButton.clicked.connect(self.addToScene)
        self.removeButton = QToolButton(self)
        self.removeButton.setText("<")
        self.removeButton.clicked.connect(self.removeFromScene)
        vLayout2.addWidget(self.addButton)
        vLayout2.addWidget(self.removeButton)
        vLayout2.addItem(QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding))
        self.layout().addLayout(vLayout2)

        self.inScene = InScene(1, self)
        self.layout().addWidget(self.inScene)
        self.updateList()

    def setIdScene(self, id):
        self.sceneId = id
        self.notInScene.setSceneId(id)
        self.inScene.setSceneId(id)

    def updateList(self):
        self.inScene.updateModel()
        self.notInScene.updateModel()

    def addToScene(self):
        for ix in self.notInScene.listView.selectionModel().selectedIndexes():
            id = self.notInScene.model.record(ix.row()).value("characterID")
            query = QSqlQuery()
            query.prepare("INSERT INTO CharacterInScene VALUES (:characterID, :sceneID);")
            query.bindValue(":characterID", id)
            query.bindValue(":sceneID", self.sceneId)
            if not query.exec_():
                print(query.lastError().text())

        self.updateList()

    def removeFromScene(self):
        for ix in self.inScene.listView.selectionModel().selectedIndexes():
            id = self.inScene.model.record(ix.row()).value("characterID")
            query = QSqlQuery()
            query.prepare("DELETE FROM CharacterInScene WHERE characterID = :characterID AND sceneID = :sceneID;")
            query.bindValue(":characterID", id)
            query.bindValue(":sceneID", self.sceneId)
            if not query.exec_():
                print(query.lastError().text())
        self.updateList()


class Widget(QWidget):
    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        vlayout = QVBoxLayout(self)
        self.comboScene = QComboBox(self)
        model = QSqlQueryModel(self)
        model.setQuery("SELECT * FROM Scene")
        self.comboScene.setModel(model)
        self.comboScene.setModelColumn(1)
        self.comboScene.currentIndexChanged.connect(self.onCurrentIndexChanged)
        hcomboLayout = QHBoxLayout()
        hcomboLayout.addWidget(QLabel("Scene: "))
        hcomboLayout.addWidget(self.comboScene)
        hcomboLayout.addItem(QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum))
        vlayout.addLayout(hcomboLayout)
        self.scene = SceneWidget(1, self)
        vlayout.addWidget(self.scene)

    def onCurrentIndexChanged(self, ix):
        id = self.sender().model().record(ix).value("sceneID")
        self.scene.setIdScene(id)


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    if not createConnection():
        sys.exit(-1)
    w = Widget()
    w.show()
    sys.exit(app.exec_())
