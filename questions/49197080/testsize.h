#ifndef TESTSIZE_H
#define TESTSIZE_H

#include <QWidget>

class QLabel;

class testsize : public QWidget {
  Q_OBJECT

public:
  explicit testsize(QWidget *parent = 0);
  ~testsize();

private:
  QLabel *image;
  QPixmap original_px;

protected:
  void resizeEvent(QResizeEvent *event);
};

#endif // TESTSIZE_H
