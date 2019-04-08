#include "mainwindow.h"
#include "drawarea.h"
#include "shape.h"

#include <QCloseEvent>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>

#include <functional>
#include <utility>

namespace DrawApp {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), brushActionGroup(this), drawArea(&undoStack) {
  prepareMainMenu();
  prepareToolBar();
  setCentralWidget(&drawArea);
  setWindowTitle(tr("DrawApp"));
  resize(700, 700);
}
MainWindow::~MainWindow() {}

void MainWindow::prepareMainMenu() {
  using namespace std::placeholders;

  menuBar()->setStyleSheet(
      "QToolButton:hover {background-color: darkgray; }"
      " QMenuBar::item:selected  {background: darkgray; }"
      " QMenu::item:selected  {background: darkgray; color: black;}"
      " QMenu {background: #fff433; }"
      " QMenuBar {background: #fff433; }");

  QMenu *const fileTab(menuBar()->addMenu(tr("&File")));
  fileTab->addAction(tr("&New"), this, SLOT(createNew()), QKeySequence::New);
  fileTab->addAction(tr("&Open"), this, SLOT(open()), QKeySequence::Open);
  fileTab->addAction("&Save", this, SLOT(save()), QKeySequence::Save);
  fileTab->addSeparator();
  fileTab->addAction(tr("&Exit"), this, SLOT(close()), QKeySequence::Quit);

  QMenu *const editTab(menuBar()->addMenu(tr("&Edit")));
  QAction *const undoAct = undoStack.createUndoAction(editTab, tr("&Undo"));
  undoAct->setShortcut(QKeySequence::Undo);
  editTab->addAction(undoAct);
  QAction *const redoAct = undoStack.createRedoAction(editTab, tr("&Redo"));
  redoAct->setShortcut(QKeySequence::Redo);
  editTab->addAction(redoAct);

  QMenu *const drawTab(menuBar()->addMenu(tr("&Draw")));
  const std::pair<QString, DrawArea::DrawingFactory> shapeActions[] = {
      std::make_pair(tr("&Pencil"), createPencil),
      std::make_pair(tr("&Eraser"), createEraser),
      std::make_pair(tr("&Rectangle"), createRectangle),
      std::make_pair(tr("E&llipse"), createEllipse),
      std::make_pair(tr("&Triangle"), createTriangle),
      std::make_pair(tr("&Fill"),
                     std::bind(createFill, &drawArea, _1, _2, _3, _4))};
  for (const auto &nameToFunction : shapeActions) {
    QAction *const chooseShapeAction(drawTab->addAction(nameToFunction.first));
    connect(chooseShapeAction, &QAction::triggered,
            std::bind(&DrawArea::setDrawingFactory, &drawArea,
                      nameToFunction.second));
    brushActionGroup.addAction(chooseShapeAction)->setCheckable(true);
  }
  brushActionGroup.setExclusive(true);
  brushActionGroup.actions().first()->trigger();
  drawTab->addSeparator();
  drawTab->addAction(tr("P&ick stroke color"), this, SLOT(pickStrokeColor()));
  drawTab->addAction(tr("Pi&ck fill color"), this, SLOT(pickFillColor()));
  drawTab->addAction(tr("Pic&k stroke width"), this, SLOT(pickStrokeWidth()));

  QMenu *const effectsTab = menuBar()->addMenu(tr("Effe&cts"));
  const std::pair<QString, std::function<void()>> effectActions[] = {
      std::make_pair(tr("Flip &horizontally"),
                     std::bind(&DrawArea::flip, &drawArea, true, false)),
      std::make_pair(tr("Flip &vertically"),
                     std::bind(&DrawArea::flip, &drawArea, false, true)),
      std::make_pair(tr("Rotate &right 90 deg"),
                     std::bind(&DrawArea::rotate, &drawArea, 90.0)),
      std::make_pair(tr("Rotate &left 90 deg"),
                     std::bind(&DrawArea::rotate, &drawArea, -90.0)),
      std::make_pair(tr("&Rotate 180 deg"),
                     std::bind(&DrawArea::rotate, &drawArea, 180.0))};
  for (const auto &effectDesc : effectActions) {
    connect(effectsTab->addAction(effectDesc.first), &QAction::triggered,
            effectDesc.second);
  }
}
void MainWindow::prepareToolBar() {
  using namespace std::placeholders;

  QToolBar *fastAccessMenu(new QToolBar());
  addToolBar(fastAccessMenu);
  fastAccessMenu->setStyleSheet(
      "QToolButton:hover {background-color: darkgray; }"
      " QToolBar {background: #fff433 }");

  QAction *usePen(new QAction);
  usePen->setIcon(QIcon("icons/pencil.png"));
  connect(usePen, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, createPencil));
  usePen->setToolTip(QString::fromStdString("Draw with a pencil"));
  fastAccessMenu->addAction(usePen);

  QAction *useEraser(new QAction);
  useEraser->setIcon(QIcon("icons/eraser.png"));
  connect(useEraser, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, createEraser));
  useEraser->setToolTip(QString::fromStdString("Erase parts of the drawing"));
  fastAccessMenu->addAction(useEraser);

  QAction *useSquare(new QAction);
  useSquare->setIcon(QIcon("icons/square.png"));
  connect(useSquare, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, createRectangle));
  useSquare->setToolTip(QString::fromStdString("Draw a rectangle"));
  fastAccessMenu->addAction(useSquare);

  QAction *useCircle(new QAction);
  useCircle->setIcon(QIcon("icons/circle.png"));
  connect(useCircle, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, createEllipse));
  useCircle->setToolTip(QString::fromStdString("Draw an ellipse"));
  fastAccessMenu->addAction(useCircle);

  QAction *useTriangle(new QAction);
  useTriangle->setIcon(QIcon("icons/triangle.png"));
  connect(useTriangle, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, createTriangle));
  useTriangle->setToolTip(QString::fromStdString("Draw a triangle"));
  fastAccessMenu->addAction(useTriangle);

  QAction *useFill(new QAction);
  useFill->setIcon(QIcon("icons/filler.png"));
  DrawArea::DrawingFactory fillFactory(
      std::bind(createFill, &drawArea, _1, _2, _3, _4));
  connect(useFill, &QAction::triggered,
          std::bind(&DrawArea::setDrawingFactory, &drawArea, fillFactory));
  useFill->setToolTip(QString::fromStdString("Fill selected area"));
  fastAccessMenu->addAction(useFill);

  fastAccessMenu->addSeparator();

  QAction *pickStrokeWidthAction(new QAction);
  pickStrokeWidthAction->setIcon(QIcon("icons/sizePicker.png"));
  connect(pickStrokeWidthAction, SIGNAL(triggered()), this,
          SLOT(pickStrokeWidth()));
  pickStrokeWidthAction->setToolTip(
      QString::fromStdString("Pick the stroke width"));
  fastAccessMenu->addAction(pickStrokeWidthAction);

  QAction *pickStrokeColorAction(new QAction);
  pickStrokeColorAction->setIcon(QIcon("icons/colorPicker.png"));
  connect(pickStrokeColorAction, SIGNAL(triggered()), this,
          SLOT(pickStrokeColor()));
  pickStrokeColorAction->setToolTip(
      QString::fromStdString("Pick the stroke color"));
  fastAccessMenu->addAction(pickStrokeColorAction);

  QAction *pickFillColorAction(new QAction);
  pickFillColorAction->setIcon(QIcon("icons/fillColor.png"));
  connect(pickFillColorAction, SIGNAL(triggered()), this,
          SLOT(pickFillColor()));
  pickFillColorAction->setToolTip(
      QString::fromStdString("Pick the stroke color"));
  fastAccessMenu->addAction(pickFillColorAction);

  fastAccessMenu->addSeparator();
}
void MainWindow::save() { saveTheDrawing(); }
void MainWindow::pickStrokeWidth() {
  bool canUseTheSpecifiedWidth(false);
  const int newWidth(QInputDialog::getInt(
      this, tr("Pen width"), tr("Pick pen width:"), drawArea.getPenWidth(), 1,
      50, 1, &canUseTheSpecifiedWidth));
  if (canUseTheSpecifiedWidth) {
    drawArea.setPenWidth(newWidth);
  }
}
void MainWindow::pickStrokeColor() {
  const QColor newColor(QColorDialog::getColor(drawArea.getPenColor()));
  if (newColor.isValid()) {
    drawArea.setStrokeColor(newColor);
  }
}
void MainWindow::pickFillColor() {
  const QColor newColor(QColorDialog::getColor(drawArea.getPenColor()));
  if (newColor.isValid()) {
    drawArea.setFillColor(newColor);
  }
}
void MainWindow::createNew() {
  if (tryToSaveBeforeClosing()) {
    drawArea.createNewDrawing();
  }
}
void MainWindow::open() {
  if (tryToSaveBeforeClosing()) {
    const QString pathToImage(QFileDialog::getOpenFileName(
        this, tr("Open file"), QDir::currentPath()));
    if (!pathToImage.isEmpty()) {
      drawArea.openDrawing(pathToImage);
    }
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (tryToSaveBeforeClosing()) {
    event->accept();
  } else {
    event->ignore();
  }
}
bool MainWindow::tryToSaveBeforeClosing() {
  if (drawArea.isModified()) {
    const QMessageBox::StandardButton res(QMessageBox::warning(
        this, tr("DrawApp"), tr("Would you like to save changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel));
    if (res == QMessageBox::Save) {
      return saveTheDrawing();
    } else if (res == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}
bool MainWindow::saveTheDrawing() {
  const QByteArray fileExtension("bmp");
  const QString initialDirectory(QDir::currentPath() + "/untitled." +
                                 fileExtension);
  const QString savedFileName(QFileDialog::getSaveFileName(
      this, tr("Save As"), initialDirectory,
      tr("%1 Files (*.%2);;All Files (*)")
          .arg(QString::fromLatin1(fileExtension))
          .arg(QString::fromLatin1(fileExtension.toUpper()))));
  return !savedFileName.isEmpty() &&
         drawArea.saveDrawing(savedFileName, fileExtension.constData());
}
} // namespace DrawApp
