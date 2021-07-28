import os
import re
import sys
from pathlib import Path

from PySide2.QtCore import (
    Property,
    QCoreApplication,
    QDir,
    QObject,
    Qt,
    QTranslator,
    QUrl,
    Signal,
    Slot,
)
from PySide2.QtGui import QGuiApplication, QStandardItem, QStandardItemModel
from PySide2.QtQml import QQmlApplicationEngine

CURRENT_DIRECTORY = Path(__file__).resolve().parent
QML_DIRECTORY = CURRENT_DIRECTORY / "qml"
TRANSLATIONS_DIR = CURRENT_DIRECTORY / "translations"


class Translator(QObject):
    language_changed = Signal(name="languageChanged")

    def __init__(self, engine, parent=None):
        super().__init__(parent)
        self._engine = engine
        self._languages_model = QStandardItemModel()
        self.load_translations()
        self._translator = QTranslator()

    @Slot(str)
    def set_language(self, language):
        if language != "Default":
            trans_dir = QDir(os.fspath(TRANSLATIONS_DIR))
            filename = trans_dir.filePath(f"i18n_{language}.qm")
            if not self._translator.load(filename):
                print("Failed")
            QGuiApplication.installTranslator(self._translator)
        else:
            QGuiApplication.removeTranslator(self._translator)
        self._engine.retranslate()

    def languages_model(self):
        return self._languages_model

    languages = Property(QObject, fget=languages_model, constant=True)

    def load_translations(self):
        self._languages_model.clear()
        item = QStandardItem("Default")
        self._languages_model.appendRow(item)
        trans_dir = QDir(os.fspath(TRANSLATIONS_DIR))
        for filename in trans_dir.entryList(["*.qm"], QDir.Files, QDir.Name):
            language = re.search(r"i18n_(.*?)\.qm", filename).group(1)
            item = QStandardItem(language)
            self._languages_model.appendRow(item)


def main():
    app = QGuiApplication(sys.argv)

    engine = QQmlApplicationEngine()

    translator = Translator(engine, app)

    engine.rootContext().setContextProperty("translator", translator)
    filename = os.fspath(QML_DIRECTORY / "main.qml")
    url = QUrl.fromLocalFile(filename)

    def handle_object_created(obj, obj_url):
        if obj is None and url == obj_url:
            QCoreApplication.exit(-1)

    engine.objectCreated.connect(handle_object_created, Qt.QueuedConnection)
    engine.load(url)

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
