import os
import sys
from pathlib import Path

from PySide2.QtCore import (
    Property,
    QCoreApplication,
    QObject,
    Qt,
    QTimer,
    QTranslator,
    QUrl,
)
from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine

CURRENT_DIRECTORY = Path(__file__).resolve().parent
QML_DIRECTORY = CURRENT_DIRECTORY / "qml"
TRANSLATIONS_DIR = CURRENT_DIRECTORY / "translations"


class PythonModel(QObject):
    def python_property(self):
        return self.tr("Python Example String")

    pythonProperty = Property(str, fget=python_property, constant=True)


def main():
    app = QGuiApplication(sys.argv)

    py_tranlator = QTranslator()
    res = py_tranlator.load(os.fspath(TRANSLATIONS_DIR / "py.qm"))
    assert res

    qml_tranlator = QTranslator()
    res = qml_tranlator.load(os.fspath(TRANSLATIONS_DIR / "qml.qm"))
    assert res

    # global_tranlator = QTranslator()
    # res = qml_tranlator.load(os.fspath(TRANSLATIONS_DIR / "global.qm"))
    # assert res

    python_model = PythonModel(app)

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("pythonModel", python_model)

    filename = os.fspath(QML_DIRECTORY / "main.qml")
    url = QUrl.fromLocalFile(filename)

    def handle_object_created(obj, obj_url):
        if obj is None and url == obj_url:
            QCoreApplication.exit(-1)

    engine.objectCreated.connect(handle_object_created, Qt.QueuedConnection)
    engine.load(url)

    ok = False

    def handle_timeout():
        nonlocal ok
        if ok:
            QCoreApplication.installTranslator(py_tranlator)
            QCoreApplication.installTranslator(qml_tranlator)
            # QCoreApplication.installTranslator(global_tranlator)
        else:
            QCoreApplication.removeTranslator(py_tranlator)
            QCoreApplication.removeTranslator(qml_tranlator)
            # QCoreApplication.removeTranslator(global_tranlator)

        engine.retranslate()

        ok = not ok

    timer = QTimer(interval=1000, timeout=handle_timeout)
    timer.start()

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
