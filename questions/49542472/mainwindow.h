#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void resizeEvent(QResizeEvent *event) override;
  void showEvent(QShowEvent *event) override;

private:
  void moveButtonFromCoord();
  Ui::MainWindow *ui;
  QPushButton *button;
};

#endif // MAINWINDOW_H
