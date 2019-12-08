import sys

from PyQt5 import QtWidgets

import QTermWidget

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    w = QTermWidget.QTermWidget()
    w.resize(640, 480)
    w.show()
    sys.exit(app.exec_())

"""
docker run -it \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=$DISPLAY \
    --device /dev/dri --device /dev/snd \
    --privileged \
    -v /run/dbus/:/run/dbus/ \
    --group-add $(getent group audio | cut -d: -f3) \
    so-59229716
"""