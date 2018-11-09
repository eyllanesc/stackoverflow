import sys

from PyQt5.QtCore import QUrl, QMetaObject, Q_ARG, QVariant, QTimer, \
    QDate
from PyQt5.QtQuickWidgets import QQuickWidget
from PyQt5.QtWidgets import QApplication

counter = 0


def onTimeout(obj):
    global counter
    value = {"lesson": str(counter), "subject": "PE", "day": QDate.longDayName(1 + counter % 7)}
    QMetaObject.invokeMethod(obj, "append", Q_ARG(QVariant, value))
    counter += 1


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = QQuickWidget()
    w.setSource(QUrl('main.qml'))
    timer = QTimer()
    timer.timeout.connect(lambda: onTimeout(w.rootObject()))
    timer.start(1000)
    w.show()
    sys.exit(app.exec_())
