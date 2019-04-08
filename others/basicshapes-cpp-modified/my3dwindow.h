#ifndef MY3DWINDOW_H
#define MY3DWINDOW_H

#include <Qt3DExtras/Qt3DWindow>

class My3DWindow : public Qt3DExtras::Qt3DWindow {
  Q_OBJECT
public:
  My3DWindow(QScreen *screen = nullptr);
  ~My3DWindow();

protected:
  void keyPressEvent(QKeyEvent *ev);
};

#endif // MY3DWINDOW_H
