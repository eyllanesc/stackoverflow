import os
from PyQt5 import QtCore, QtWidgets, QtMultimedia, QtMultimediaWidgets


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        video_widget = QtMultimediaWidgets.QVideoWidget()
        player = QtMultimedia.QMediaPlayer(
            self, QtMultimedia.QMediaPlayer.VideoSurface)
        file = os.path.join(os.path.dirname(
            os.path.realpath(__file__)), "video.mp4")
        player.setMedia(QtMultimedia.QMediaContent(
            QtCore.QUrl.fromLocalFile(file)))
        player.setVideoOutput(video_widget)
        player.play()
        self.setCentralWidget(video_widget)


if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())
