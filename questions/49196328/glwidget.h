#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QWidget>

class GLWidget : public QGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit GLWidget(QWidget *parent = 0, QGLWidget *shareWidget = 0);
  ~GLWidget();

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  void keyPressEvent(QKeyEvent *e);

private:
  int sample;
};

#endif // GLWIDGET_H
