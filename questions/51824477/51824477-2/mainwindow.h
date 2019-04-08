#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  Q_PROPERTY(double dataGauge READ dataGauge WRITE setDataGauge NOTIFY
                 dataGaugeChanged)

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  double dataGauge() const;
  void setDataGauge(double dataGauge);
signals:
  void dataGaugeChanged();

private:
  Ui::MainWindow *ui;
  double mDataGauge;
};

#endif // MAINWINDOW_H
