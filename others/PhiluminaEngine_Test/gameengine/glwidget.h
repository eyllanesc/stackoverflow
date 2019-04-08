#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "nodes/2d/sprite/csprite2d.h"
#include <QOpenGLWidget>
#include <QWidget>

/**
 * @brief
 *
 */
class GLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  /**
   * @brief
   *
   * @param parent
   */
  GLWidget(QWidget *parent);
  void addSprite(CSprite2D *sprite);

public slots:
  /**
   * @brief
   *
   */
  void animate();

protected:
  /**
   * @brief
   *
   * @param event
   */
  void paintEvent(QPaintEvent *event) override;

private:
  int direction = 1; /**< TODO: describe */
  QList<CSprite2D *> sprites;
};

#endif // GLWIDGET_H
