#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include "nodes/2d/sprite/csprite2d.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    CSprite2D *sprite;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int direction = 1;
};

#endif // GLWIDGET_H
