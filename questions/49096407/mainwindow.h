#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void newTabActionHandler();

private:
  QList<QWidget *> widgetList;
  QList<QTextEdit *> textEditList;
  QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
