#include "glwidget.h"
#include <GL/freeglut.h>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

GLWidget::GLWidget(QWidget* parent):QGLWidget(parent)
{

    setMinimumSize(200, 200);
}

void GLWidget::initializeGL()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(100,500);
    glVertex2f(500,100);
    glEnd();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    //QPixmap pixmap = QPixmap::fromImage(grabFrameBuffer(1));
    QPixmap pixmap = renderPixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());
    drag->exec(Qt::CopyAction);
}
