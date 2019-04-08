#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QString title() const;
  void setTitle(const QString &title);

  QPointF center() const;
  void setCenter(const QPointF &center);
signals:
  void titleChanged();
  void centerChanged();

private:
  Ui::MainWindow *ui;
  QString m_title;
  QPointF m_center;
};

#endif // MAINWINDOW_H
