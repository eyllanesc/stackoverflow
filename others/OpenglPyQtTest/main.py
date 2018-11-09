import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.uic import *

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

class mainWindow(QMainWindow):

    def __init__(self, *args):
        super(mainWindow, self).__init__(*args)
        loadUi('minimal.ui', self)

    def setupUI(self):
    	self.openGLWidget.initializeGL()
    	self.openGLWidget.resizeGL(651,551)
    	self.openGLWidget.paintGL = self.paintGL
    	timer = QTimer(self)
    	timer.timeout.connect(self.openGLWidget.update) 
    	timer.start(1000)

    def paintGL(self):
    	glClear(GL_COLOR_BUFFER_BIT)
    	glColor3f(1,0,0);
    	glBegin(GL_TRIANGLES);
    	glVertex3f(-0.5,-0.5,0);
    	glVertex3f(0.5,-0.5,0);
    	glVertex3f(0.0,0.5,0);
    	glEnd()

    	gluPerspective(45, 651/551, 0.1, 50.0)
    	glTranslatef(0.0,0.0, -5)
	        


app = QApplication(sys.argv)
window = mainWindow()
window.setupUI()
window.show()
sys.exit(app.exec_())