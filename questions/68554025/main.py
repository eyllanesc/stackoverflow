import os
import sys
from pathlib import Path

from PyQt5.QtCore import (
    QAbstractTableModel,
    QDir,
    QEvent,
    QModelIndex,
    Qt,
    QT_TRANSLATE_NOOP,
    QTranslator,
)
from PyQt5.QtWidgets import QApplication, QComboBox, QTableView, QVBoxLayout, QWidget

import numpy as np

CURRENT_DIRECTORY = Path(__file__).resolve().parent


class Model(QAbstractTableModel):
    def __init__(self, parent=None):
        super().__init__(parent)
        self._data = np.random.randint(0, 100, size=(10, 4))  # type: np.ndarray
        self._columns = [
            QT_TRANSLATE_NOOP("Model", "First"),
            QT_TRANSLATE_NOOP("Model", "Second"),
            QT_TRANSLATE_NOOP("Model", "Third"),
            QT_TRANSLATE_NOOP("Model", "Fourth"),
        ]

    def rowCount(self, parent: QModelIndex = QModelIndex()) -> int:
        if parent.isValid():
            return 0
        return self._data.shape[0]

    def columnCount(self, parent: QModelIndex = QModelIndex()) -> int:
        if parent.isValid():
            return 0
        return self._data.shape[1]

    def headerData(self, section: int, orientation: Qt.Orientation, role: int):
        if role == Qt.DisplayRole and orientation == Qt.Horizontal:
            return self.tr(self._columns[section])

    def data(self, index, role=Qt.DisplayRole):
        if role == Qt.DisplayRole:
            return str(self._data[index.row()][index.column()])


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.translator = QTranslator()
        model = Model(self)
        self.combobox = QComboBox()
        tableview = QTableView()
        tableview.setModel(model)

        lay = QVBoxLayout(self)
        lay.addWidget(self.combobox)
        lay.addWidget(tableview)

        dir_translations = os.fspath(CURRENT_DIRECTORY / "translations")
        trans_dir = QDir(dir_translations)
        self.combobox.addItem("Default")
        for filename in trans_dir.entryList(["*.qm"], QDir.Files, QDir.Name):
            self.combobox.addItem(filename, trans_dir.filePath(filename))

        self.combobox.currentIndexChanged.connect(self.handle_current_index_changed)

    def handle_current_index_changed(self, index):
        qmfile = self.combobox.itemData(index)
        if qmfile:
            self.translator.load(qmfile)
            QApplication.installTranslator(self.translator)
        else:
            QApplication.removeTranslator(self.translator)


def main():
    app = QApplication(sys.argv)
    w = Widget()
    w.resize(640, 480)
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
