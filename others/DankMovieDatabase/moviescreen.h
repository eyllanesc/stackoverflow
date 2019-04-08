#ifndef MOVIESCREEN_H
#define MOVIESCREEN_H

#include <QJsonObject>
#include <QMovie>
#include <QWidget>

namespace Ui {
class MovieScreen;
}

class MovieScreen : public QWidget {
  Q_OBJECT

public:
  explicit MovieScreen(QWidget *parent = 0);
  ~MovieScreen();

  QJsonObject getObject() const;
  void setObject(const QJsonObject &value);

private slots:
  void setPoster();

private:
  Ui::MovieScreen *ui;
  QJsonObject object;
  QMovie *movie;

  void setInfo();
};

#endif // MOVIESCREEN_H
