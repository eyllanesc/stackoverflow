from functools import wraps
from time import time

import cv2
import numpy as np
from PyQt5 import QtGui, QtCore, QtQuick, QtQml

from PyCVQML import CVAbstractFilter


def timing(f):
    @wraps(f)
    def wrap(*args, **kw):
        ts = time()
        result = f(*args, **kw)
        te = time()
        print('func:%r took: %2.4f sec' % (f.__name__, te - ts))
        return result
    return wrap


@timing
def max_rgb_filter(image):
    # split the image into its BGR components
    (B, G, R) = cv2.split(image)

    # find the maximum pixel intensity values for each
    # (x, y)-coordinate,, then set all pixel values less
    # than M to zero
    M = np.maximum(np.maximum(R, G), B)
    R[R < M] = 0
    G[G < M] = 0
    B[B < M] = 0

    # merge the channels back together and return the image
    return cv2.merge([B, G, R])


@timing
def rgb_to_gray(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    return gray


class MaxRGBFilter(CVAbstractFilter):
    def process_image(self, src):
        return max_rgb_filter(src)


class GrayFilter(CVAbstractFilter):
    def process_image(self, src):
        return rgb_to_gray(src)


if __name__ == '__main__':
    import os
    import sys

    app = QtGui.QGuiApplication(sys.argv)
    QtQml.qmlRegisterType(MaxRGBFilter, "Filters", 1, 0, "MaxRGBFilter")
    QtQml.qmlRegisterType(GrayFilter, "Filters", 1, 0, "GrayFilter")

    dir_path = os.path.dirname(os.path.realpath(__file__))

    view = QtQuick.QQuickView()
    view.setTitle("PyCVQML Example")
    view.setSource(QtCore.QUrl.fromLocalFile(QtCore.QDir(dir_path).absoluteFilePath("main.qml")))
    view.show()
    sys.exit(app.exec_())
