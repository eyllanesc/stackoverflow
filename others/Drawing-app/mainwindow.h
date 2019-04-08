#ifndef _TROFIMOV_MAIN_WINDOW_H_
#define _TROFIMOV_MAIN_WINDOW_H_

#include "drawarea.h"

#include <QActionGroup>
#include <QMainWindow>
#include <QUndoStack>

namespace DrawApp {
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent *);

private slots:
  void createNew();
  void open();
  void save();

  void pickStrokeColor();
  void pickFillColor();
  void pickStrokeWidth();

private:
  QActionGroup brushActionGroup;
  QUndoStack undoStack;
  DrawArea drawArea;

  void prepareMainMenu();
  void prepareToolBar();
  bool tryToSaveBeforeClosing();
  bool saveTheDrawing();
};
} // namespace DrawApp

#endif
