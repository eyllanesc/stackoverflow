import sys
from PyQt4 import QtCore
from PyQt4.QtGui import *
from splitter_main import Ui_frmMain
import math

class CustomLine(QGraphicsLineItem):
    visible = True
    def __init__(self,x1, y1, x2, y2, lines, parent=None, scene=None):
        super(CustomLine, self).__init__(x1, y1, x2, y2, parent, scene)
        self.lines = lines

    def mousePressEvent(self, QGraphicsSceneMouseEvent):
        print('Mouse released')
        if self.visible:
            self.scene().removeItem(self)
            print(self.lines)
            print(self)
            self.lines.remove(self)
            print(self.lines)
            self.visible = False

class MyForm(QMainWindow):
    line_width = 1
    h_lines, v_lines = 0, 0
    lineColor = QtCore.Qt.red
    draw_scale_x, draw_scale_y = 1.0, 1.0

    w, h = 0, 0
    scene_w, scene_h = 0, 0
    wcm, hcm = 0.0, 0.0
    in2cm = 2.54

    supported_images = ['BW', 'EPS', 'EPSF', 'EPSI', 'EXR', 'PCX', 'PSD', 'RAS', 'RGB', 'RGBA', 'SGI', 'TGA', 'XCF', 'bmp', 'bw', 'dds', 'eps', 'epsf', 'epsi', 'exr', 'gif', 'ico', 'jp2', 'jpeg', 'jpg', 'mng', 'pbm', 'pcx', 'pgm', 'pic', 'png', 'ppm', 'psd', 'ras', 'rgb', 'rgba', 'sgi', 'svg', 'svgz', 'tga', 'tif', 'tiff', 'webp', 'xbm', 'xcf', 'xpm', 'xv']
    image_filter = 'Images (*.BW *.EPS *.EPSF *.EPSI *.EXR *.PCX *.PSD *.RAS *.RGB *.RGBA *.SGI *.TGA *.XCF *.bmp *.bw *.dds *.eps *.epsf *.epsi *.exr *.gif *.ico *.jp2 *.jpeg *.jpg *.mng *.pbm *.pcx *.pgm *.pic *.png *.ppm *.psd *.ras *.rgb *.rgba *.sgi *.svg *.svgz *.tga *.tif *.tiff *.webp *.xbm *.xcf *.xpm *.xv )'
    h_lines_list = []
    v_lines_list = []
    scene = None
    image = None

    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_frmMain()
        self.ui.setupUi(self)
        self.ui.actionOpen_Image.triggered.connect(self.open_image)
        self.ui.actionExit.triggered.connect(self.exit)
        self.center()
        self.ui.btnReset.clicked.connect(self.reset)
        self.ui.btnSubmit.clicked.connect(self.submit)
        for c in self.ui.grpControls.children():
            # print('This: %s'%(type(c)))
            if isinstance(c, QLabel):
                c.adjustSize()
        self.line_width = int(self.ui.txtLineWidth.text())
        self.draw_scale_y = float(self.ui.txtScaleHeight.text())
        self.draw_scale_x = float(self.ui.txtScaleWidth.text())
        self.h_lines = int(self.ui.txtHorizontal.text())
        self.v_lines = int(self.ui.txtVertical.text())
        self.lineColor = self.ui.cbColor.color()
        self.statusBar().showMessage('App Started')

    def reset(self):
        # print('Reset')
        for l in self.h_lines_list:
            self.scene.removeItem(l)
        self.h_lines_list = []
        for l in self.v_lines_list:
            self.scene.removeItem(l)
        self.v_lines_list = []

        self.ui.txtLineWidth.setText('1')
        self.ui.txtScaleWidth.setText('1')
        self.ui.txtScaleHeight.setText('1')
        self.ui.txtHorizontal.setText('0')
        self.ui.txtVertical.setText('0')
        self.ui.cbColor.setColor(QtCore.Qt.red)

        self.line_width = int(self.ui.txtLineWidth.text())
        self.draw_scale_y = float(self.ui.txtScaleHeight.text())
        self.draw_scale_x = float(self.ui.txtScaleWidth.text())
        self.h_lines = int(self.ui.txtHorizontal.text())
        self.v_lines = int(self.ui.txtVertical.text())
        self.lineColor = self.ui.cbColor.color()

        self.statusBar().showMessage('Back to defaults')

    def submit(self):
        for l in self.h_lines_list:
            self.scene.removeItem(l)
        self.h_lines_list = []
        for l in self.v_lines_list:
            self.scene.removeItem(l)
        self.v_lines_list = []

        self.line_width = int(self.ui.txtLineWidth.text())
        self.draw_scale_y = float(self.ui.txtScaleHeight.text())
        self.draw_scale_x = float(self.ui.txtScaleWidth.text())
        self.h_lines = int(self.ui.txtHorizontal.text())
        self.v_lines = int(self.ui.txtVertical.text())
        self.lineColor = self.ui.cbColor.color()

        hspace, vspace = self.scene_h / (self.h_lines + 1), self.scene_w / (self.v_lines + 1)
        hstart, vstart = 0, 0
        for i in range(self.h_lines):
            hstart += hspace
            self.drawLine(0, hstart, self.scene_w, hstart, self.h_lines_list)
        for i in range(self.v_lines):
            vstart += vspace
            self.drawLine(vstart, 0, vstart, self.scene_h, self.v_lines_list)

        self.statusBar().showMessage('Splitted the image')

    def drawLine(self, x1, y1, x2, y2, lines_list):
        pen = QPen(self.lineColor)
        pen.setWidth(self.line_width)
        l = CustomLine(x1, y1, x2, y2, lines_list, scene=self.scene)
        l.setAcceptedMouseButtons(QtCore.Qt.LeftButton)
        l.setPen(pen)
        lines_list.append(l)

    def center(self):
        frameGm = self.frameGeometry()
        screen = QApplication.desktop().\
            screenNumber(QApplication.desktop().cursor().pos())
        centerPoint = QApplication.desktop().screenGeometry(screen).center()
        frameGm.moveCenter(centerPoint)
        self.move(frameGm.topLeft())

    def open_image(self):
        fileName = QFileDialog.getOpenFileName(self, 'Open Image',
                                                     QtCore.QDir.currentPath(),
                                                     self.image_filter)
        if fileName:
            self.reset()
            self.image = QImage(fileName)
            self.scene = QGraphicsScene(self)
            pm = QPixmap(self.image)
            pm = pm.scaled(self.ui.imgView.size(), QtCore.Qt.KeepAspectRatio,
                           QtCore.Qt.SmoothTransformation)
            pmItem = QGraphicsPixmapItem(pm, None, self.scene)
            pmItem.setAcceptHoverEvents(True)
            pmItem.hoverMoveEvent = self.pixelSelect
            pmItem.hoverLeaveEvent = self.hover_leave

            # self.ui.imgView.fitInView(self.scene.sceneRect(), QtCore.Qt.KeepAspectRatio)
            self.ui.imgView.setScene(self.scene)
            # self.scene.addPixmap(pm)
            self.w, self.h = self.image.width(), self.image.height()
            self.scene_w = self.scene.sceneRect().width()
            self.scene_h = self.scene.sceneRect().height()
            self.wcm = round(self.scene.width() / QX11Info.appDpiX() * self.in2cm, 2)
            self.hcm = round(self.scene.height() / QX11Info.appDpiY() * self.in2cm, 2)

            self.ui.lblWidth.setText(str(self.w) + ' px')
            self.ui.lblWidth.adjustSize()
            self.ui.lblHeight.setText(str(self.h) + ' px')
            self.ui.lblHeight.adjustSize()
            self.ui.lblWidthCm.setText(str(self.wcm) + ' cm')
            self.ui.lblWidthCm.adjustSize()
            self.ui.lblHeightCm.setText(str(self.hcm) + ' cm')
            self.ui.lblHeightCm.adjustSize()

            self.statusBar().showMessage('Loaded image %s'%(fileName))

    def hover_leave(self, event):
        for l in self.v_dist_lines:
            self.scene.removeItem(l)
        self.v_dist_lines = []
        for l in self.h_dist_lines:
            self.scene.removeItem(l)
        self.h_dist_lines = []
        for t in self.txt_dist_list:
            self.scene.removeItem(t)
        self.txt_dist_list = []

    v_dist_lines = []
    h_dist_lines = []
    txt_dist_list = []
    oldColor = None
    oldPosition = None
    def pixelSelect(self, event):
        for l in self.v_dist_lines:
            self.scene.removeItem(l)
        self.v_dist_lines = []
        for l in self.h_dist_lines:
            self.scene.removeItem(l)
        self.h_dist_lines = []
        for t in self.txt_dist_list:
            self.scene.removeItem(t)
        self.txt_dist_list = []

        position = QtCore.QPoint(event.pos().x(), event.pos().y())
        closest_h_line, closest_v_line = None, None
        dist_h, dist_v = self.scene_h, self.scene_w
        for l in self.h_lines_list:
            diff = math.fabs(position.y() - l.line().y1())
            if diff < dist_h:
                dist_h = diff
                closest_h_line = l

        for l in self.v_lines_list:
            diff = math.fabs(position.x() - l.line().x1())
            if diff < dist_v:
                dist_v = diff
                closest_v_line = l

        diff_h = round(float(dist_h) / QX11Info.appDpiY() * self.in2cm * (self.draw_scale_y / self.hcm), 2)
        diff_v = round(float(dist_v) / QX11Info.appDpiX() * self.in2cm * (self.draw_scale_x / self.wcm), 2)

        # print(diff_h, diff_v)

        result = ''
        if closest_h_line:
            result += 'Distance to nearest horizontal line is {:0.2f} cm'.format(diff_h)
            result += ',\t'
            self.drawLine(position.x(), position.y(),
                          position.x(), closest_h_line.line().y1(), self.h_dist_lines)
            txt = QGraphicsTextItem(QtCore.QString('{:0.2f}cm'.format(diff_h)),
                                    scene=self.scene)
            txt_x = position.x() + 10
            y_diff = abs(position.y() - closest_h_line.line().y1()) / 2
            txt_y = position.y() + y_diff if closest_h_line.line().y1() > position.y() \
                else position.y() - y_diff
            txt.setPos(QtCore.QPointF(txt_x,
                                      txt_y))
            self.txt_dist_list.append(txt)
        if closest_v_line:
            result += 'Distance to nearest vertical line is {:0.2f} cm'.format(diff_v)
            self.drawLine(position.x(), position.y(),
                          closest_v_line.line().x1(), position.y(), self.v_dist_lines)
            txt = QGraphicsTextItem(QtCore.QString('{:0.2f}cm'.format(diff_v)),
                                    scene=self.scene)
            x_diff = abs(position.x() - closest_v_line.line().x1()) / 2
            txt_x = position.x() + x_diff if closest_h_line.line().x1() > position.x() \
                else position.x() - x_diff
            txt_y = position.y() + 10
            txt.setPos(QtCore.QPointF(txt_x,
                                      txt_y))
            self.txt_dist_list.append(txt)

        self.statusBar().showMessage(result)
        # if self.oldColor and self.oldPosition:
        #     self.image.setPixel(self.oldPosition.x(), self.oldPosition.y(),
        #                         self.oldColor)
        #
        # position = QtCore.QPoint(event.pos().x(), event.pos().y())
        # color = QColor.fromRgb(self.image.pixel(position))
        # self.oldColor = qRgba(color.red(), color.blue(), color.green(), color.alpha())
        # self.oldPosition = position
        # self.image.setPixel(position.x(), position.y(),
        #                         qRgba(255, 0, 0, 255))

        #
        # if color.isValid():
        #     rgbColor = '(' + str(color.red()) + ',' + str(color.green()) + ',' + str(color.blue()) + ',' + str(
        #         color.alpha()) + ')'
        #     print('Pixel position = (' + str(event.pos().x()) + ' , ' + str(
        #         event.pos().y()) + ') - Value (R,G,B,A)= ' + rgbColor)
        # else:
        #     print(
        #         'Pixel position = (' + str(event.pos().x()) + ' , ' + str(event.pos().y()) + ') - color not valid')

    def exit(self):
        self.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    myapp = MyForm()
    myapp.show()
    sys.exit(app.exec_())