#ifndef SUMMARY_H
#define SUMMARY_H

#include <QWidget>

namespace Ui {
class Summary;
}

class Summary : public QWidget {
  Q_OBJECT

public:
  explicit Summary(QWidget *parent = 0);
  ~Summary();

private:
  Ui::Summary *ui;
};

#endif // SUMMARY_H
