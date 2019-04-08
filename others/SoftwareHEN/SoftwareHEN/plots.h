#ifndef PLOTS_H
#define PLOTS_H

#include <QWidget>

namespace Ui {
class plots;
}

class plots : public QWidget {
  Q_OBJECT

public:
  explicit plots(QWidget *parent = 0);
  ~plots();

private slots:
  void on_tabWidget_currentChanged(int index);

private:
  Ui::plots *ui;
};

#endif // PLOTS_H
