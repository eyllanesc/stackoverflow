import os
import sys

import platform

from PyQt5 import QtCore

current_dir = os.path.dirname(os.path.realpath(__file__))
style_dir = os.path.join(current_dir, "qtstyleplugins", "plugins", "styles")

if len(sys.argv) >= 2:
    style_dir = sys.argv[1]

qt_plugin_path = QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.PluginsPath)

extension = {"Linux": "*.so", "Darwin": "*.dylib", "Windows": "*.dll",}[
    platform.system()
]

for f in QtCore.QDir(style_dir).entryInfoList([extension], QtCore.QDir.Files):

    new_path = os.path.join(qt_plugin_path, "styles", f.fileName())
    QtCore.QFile.copy(f.absoluteFilePath(), new_path)

    print(f.absoluteFilePath(), "==>", new_path)
