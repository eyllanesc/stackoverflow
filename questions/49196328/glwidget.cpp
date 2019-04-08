#include "glwidget.h"

#include <QKeyEvent>
#include <QMainWindow>

GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget) {
  sample = 0;
  setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() { initializeOpenGLFunctions(); }

void GLWidget::paintGL() {

  glClearColor(0.1, 0.6, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  switch (sample) {
  case 0:
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_LINE);
    glVertex2f(-50, 0);
    glVertex2f(50, 0);
    glEnd();
    break;
    //--------------------------------
  case 1:
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(-50, 0);
    glColor3f(0, 0, 1);
    glVertex2f(50, 0);
    glEnd();
    break;
    //--------------------------------
  case 2:
    glBegin(GL_LINES);
    glVertex2f(-50, 0);
    glVertex2f(50, 0);

    glVertex2f(0, -50);
    glVertex2f(0, 50);
    glEnd();
    break;
    //--------------------------------
  case 3:
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 1, 0);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();
    break;
    //--------------------------------
  case 4:
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();
    break;
    //--------------------------------
  case 5:
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();
    glLineWidth(1);
    break;
  }
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height); // set viewport, don't rely on default values

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
}

void GLWidget::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
  case 'A':
    sample = sample < 5 ? sample + 1 : sample;
    break;
  case 'S':
    sample = sample > 0 ? sample - 1 : sample;
  };

  if (parentWidget())
    parentWidget()->setWindowTitle(QString::number(sample));

  updateGL();
}
