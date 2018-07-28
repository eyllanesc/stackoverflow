from pathlib import Path

from PyQt5.QtCore import pyqtSignal, pyqtProperty, QUrl, QPointF
from PyQt5.QtGui import QGuiApplication, QColor, QSurfaceFormat
from PyQt5.QtQml import QQmlApplicationEngine, QQmlComponent, qmlRegisterType
from PyQt5.QtQuick import QQuickItem, QSGGeometryNode, QSGGeometry, QSGNode, QSGFlatColorMaterial


class StraightLine(QQuickItem):
    p1_Changed = pyqtSignal()
    p2_Changed = pyqtSignal()
    segment_count_Changed = pyqtSignal()

    def __init__(self, parent: QQuickItem, p1: QPointF = QPointF(0, 0), p2: QPointF = QPointF(1, 1),
                 segment_count: int = 2):
        super().__init__(parent)
        self._p1 = p1
        self._p2 = p2
        self._segment_count = segment_count
        self.setFlag(QQuickItem.ItemHasContents, True)

    @pyqtProperty("QPointF", notify=p1_Changed)
    def p1(self):
        return self._p1

    @p1.setter
    def p1(self, p1: QPointF):
        if p1 == self._p1:
            return

        self._p1 = p1
        self.p1_Changed.emit()
        self.update()

    @pyqtProperty("QPointF", notify=p2_Changed)
    def p2(self):
        return self._p2

    @p2.setter
    def p2(self, p2: QPointF):
        if p2 == self._p2:
            return

        self._p2 = p2
        self.p2_Changed.emit()
        self.update()

    @pyqtProperty(int, notify=segment_count_Changed)
    def segment_count(self):
        return self._segment_count

    @segment_count.setter
    def segment_count(self, count: int):
        if count == self._segment_count:
            return

        self._segment_count = count
        self.segment_count_Changed.emit()
        self.update()

    def updatePaintNode(self, oldNode: QSGGeometryNode, _):
        if oldNode == None:
            node = QSGGeometryNode()
            geometry = QSGGeometry(QSGGeometry.defaultAttributes_Point2D(), self._segment_count)
            geometry.setLineWidth(3)
            geometry.setDrawingMode(QSGGeometry.DrawLineStrip)
            node.setGeometry(geometry)
            node.setFlag(QSGNode.OwnsGeometry)

            material = QSGFlatColorMaterial()
            material.setColor(QColor(45, 100, 120))
            node.setMaterial(material)
            node.setFlag(QSGNode.OwnsMaterial)
        else:
            node = oldNode
            geometry = node.geometry()
            geometry.allocate(self._segment_count)

        itemSize = self.size()
        vertices = geometry.vertexDataAsPoint2D()

        x1 = self._p1.x()
        y1 = self._p1.y()
        vertices[0].set(x1, y1)

        x2 = self._p2.x()
        y2 = self._p2.y()
        vertices[1].set(x2, y2)

        print(vertices[1].x)

        node.markDirty(QSGNode.DirtyGeometry)

        return node


if __name__ == "__main__":
    import sys

    path = Path("..")
    resolved_path = path.resolve()

    # Create an instance of the application
    app = QGuiApplication(sys.argv)

    # Set antialising 4 samples
    """format = QSurfaceFormat()
    format.setSamples(4)
    QSurfaceFormat.setDefaultFormat(format)"""

    # register custom types
    qmlRegisterType(StraightLine, "CustomGeometry", 1, 0, "StraightLine")

    # Create QML engine
    engine = QQmlApplicationEngine()

    # Load the qml file into the engine
    engine.addImportPath(str(resolved_path))

    engine.load("main/main.qml")

    if not engine.rootObjects():
        sys.exit(-1)

    # load the components
    component = QQmlComponent(engine)
    component.loadUrl(QUrl("components/Class.qml"))
    line_component = QQmlComponent(engine)
    line_component.loadUrl(QUrl("components/Edge.qml"))
    # check for component creation errors
    for error in component.errors():
        print(error.toString())
    # check for component creation errors
    for error in line_component.errors():
        print(error.toString())

    classes = []
    for index, class_name in enumerate(["Person", "Home"]):
        # create a new instance of the component
        cclass = component.create()
        # set the class name property of the component
        cclass.setProperty("className", class_name)
        cclass.setX((cclass.width() + 50) * index)
        cclass.setParentItem(engine.rootObjects()[0].findChild(QQuickItem))
        classes.append(cclass)

    line = line_component.beginCreate(engine.rootContext())
    line.setProperty("anchor1", classes[0])
    line.setProperty("anchor2", classes[1])
    line_component.completeCreate()

    # check for object creation errors
    for error in line_component.errors():
        print(error.toString())
    for error in component.errors():
        print(error.toString())

    engine.quit.connect(app.quit)
    sys.exit(app.exec_())
