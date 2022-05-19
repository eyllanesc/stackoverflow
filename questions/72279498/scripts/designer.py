import sys
import os.path

from PyQt5.QtCore import QCoreApplication, QLibraryInfo, QProcess, QProcessEnvironment


def main():
    app = QCoreApplication([])
    base_dir = os.path.dirname(__file__)
    plugins_dir = os.path.join(base_dir, "plugins")
    lib_dir = os.path.join(base_dir, "..", "src", "lib")

    env = QProcessEnvironment.systemEnvironment()
    env.insert("PYQTDESIGNERPATH", plugins_dir)
    env.insert("PYTHONPATH", lib_dir)

    # Start Designer.
    designer = QProcess()
    designer.setProcessEnvironment(env)

    designer_bin = QLibraryInfo.location(QLibraryInfo.BinariesPath)

    if sys.platform == "darwin":
        designer_bin += "/Designer.app/Contents/MacOS/Designer"
    else:
        designer_bin += "/designer"

    designer.start(designer_bin)
    designer.waitForFinished(-1)

    sys.exit(designer.exitCode())


if __name__ == "__main__":
    main()
