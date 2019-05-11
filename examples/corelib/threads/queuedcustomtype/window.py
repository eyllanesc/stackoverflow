from Qt import QtCore, QtGui, QtWidgets

from renderthread import RenderThread
from block import Block


class Window(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.m_thread = RenderThread()
        self.m_pixmap = QtGui.QPixmap()
        self.m_path = ""

        self.label = QtWidgets.QLabel(alignment=QtCore.Qt.AlignCenter)
        self.loadButton = QtWidgets.QPushButton(self.tr("&Load image..."))
        self.resetButton = QtWidgets.QPushButton(
            self.tr("&Stop"), enabled=False
        )

        self.loadButton.clicked.connect(self.loadImage)
        self.resetButton.clicked.connect(self.m_thread.stopProcess)
        self.m_thread.finished.connect(self.resetUi)

        self.m_thread.sendBlock.connect(self.addBlock)

        buttonLayout = QtWidgets.QHBoxLayout()
        buttonLayout.addStretch()
        buttonLayout.addWidget(self.loadButton)
        buttonLayout.addWidget(self.resetButton)

        layout = QtWidgets.QVBoxLayout(self)
        layout.addWidget(self.label)
        layout.addLayout(buttonLayout)

        self.setWindowTitle(self.tr("Queued Custom Type"))

    def loadImage(self, image):
        formats = []
        for fmt in QtGui.QImageReader.supportedImageFormats():
            if fmt.toLower() == fmt:
                formats.append("*." + fmt.data().decode())
        newPath, _ = QtWidgets.QFileDialog.getOpenFileName(
            self,
            self.tr("Open Image"),
            self.m_path,
            self.tr("Image files (%s)") % (" ".join(formats)),
        )
        if newPath:
            image = QtGui.QImage(newPath)
            if not image.isNull():
                self._loadImage(image)
                self.m_path = newPath

    def _loadImage(self, image):
        useImage = QtGui.QImage()
        space = QtGui.QGuiApplication.primaryScreen().availableGeometry()
        if (
            image.width() > 0.75 * space.width()
            or image.height() > 0.75 * space.height()
        ):
            useImage = image.scaled(
                0.75 * space.width(),
                0.75 * space.height(),
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation,
            )
        else:
            useImage = image
        self.m_pixmap = QtGui.QPixmap(useImage.width(), useImage.height())
        self.m_pixmap.fill(QtGui.qRgb(255, 255, 255))
        self.label.setPixmap(self.m_pixmap)
        self.loadButton.setEnabled(False)
        self.resetButton.setEnabled(True)
        self.m_thread.processImage(useImage)

    @QtCore.Slot(Block)
    def addBlock(self, block):
        color = block.color
        color.setAlpha(64)

        painter = QtGui.QPainter()
        painter.begin(self.m_pixmap)
        painter.fillRect(block.rect, color)
        painter.end()
        self.label.setPixmap(self.m_pixmap)

    def resetUi(self):
        self.loadButton.setEnabled(True)
        self.resetButton.setEnabled(False)

    def closeEvent(self, event):
        self.m_thread.stopProcess()
        self.m_thread.wait()
        super().closeEvent(event)
