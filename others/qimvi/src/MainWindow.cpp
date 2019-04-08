#include "MainWindow.h"
#include "ui_AboutDialog.h"
#include "ui_ResizeDialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QImageWriter>
#include <QMouseEvent>
#include <QScrollBar>
#include <QStandardPaths>
#include <functional>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  OnMouseMove(QPoint());
  OnSelectionDrag(QRect());

  connect(ui.actionSaveAs, &QAction::triggered, this, &MainWindow::OnSaveAs);
  connect(ui.actionZoomIn, &QAction::triggered, this, &MainWindow::OnZoomIn);
  connect(ui.actionZoomOut, &QAction::triggered, this, &MainWindow::OnZoomOut);
  connect(ui.actionFitWindow, &QAction::triggered, this,
          &MainWindow::OnFitWindow);
  connect(ui.actionFitActual, &QAction::triggered, this,
          &MainWindow::OnFitActual);
  connect(ui.actionRotateLeft, &QAction::triggered, this,
          &MainWindow::OnRotateLeft);
  connect(ui.actionRotateRight, &QAction::triggered, this,
          &MainWindow::OnRotateRight);
  connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::OnAbout);
  connect(ui.actionCrop, &QAction::triggered, this, &MainWindow::OnCrop);

  connect(ui.actionUndo, &QAction::triggered, this, &MainWindow::OnUndo);
  connect(ui.actionRedo, &QAction::triggered, this, &MainWindow::OnRedo);
  connect(ui.actionResize, &QAction::triggered, this, &MainWindow::OnResize);
  connect(ui.actionFullScreen, &QAction::triggered, this,
          &MainWindow::OnFullScreen);

  connect(ui.actionToGrayscale, &QAction::triggered, this,
          &MainWindow::OnConvertToGrayscale);

  ui.statusBar->addPermanentWidget(new QLabel(), 1);
  ui.statusBar->addPermanentWidget(statusSelectionRect, 1);
  ui.statusBar->addPermanentWidget(statusMousePos, 1);

  SetupFileBrowser();
}

MainWindow::~MainWindow() {}

void MainWindow::SetupFileBrowser() {
  // http://doc.qt.io/qt-5/qfilesystemmodel.html
  dirTreeModel = new QFileSystemModel(this);
  dirTreeModel->setRootPath(dirTreeModel->myComputer().toString());
  dirTreeModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
  dirTreeModel->setResolveSymlinks(true);

  fileListModel = new QFileSystemModel(this);
  fileListModel->setRootPath(dirTreeModel->myComputer().toString());
  fileListModel->setFilter(QDir::Files | QDir::NoDotAndDotDot);
  QStringList filters;
  filters << "*.jpg"
          << "*.jpeg"
          << "*.png"
          << "*.gif";
  fileListModel->setNameFilters(filters);

  auto desktop =
      QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)
          .first();

  ui.dirTreeView->setModel(
      dirTreeModel); // Ustawia model, który ma być wyświetlony przez QTreeView.
  ui.dirTreeView->setSelectionMode(
      QAbstractItemView::SingleSelection); // Pozwala na wybranie tylko jednego
                                           // folderu.
  ui.dirTreeView->setCurrentIndex(dirTreeModel->index(desktop));

  ui.fileListView->setModel(fileListModel);
  ui.fileListView->setRootIndex(fileListModel->index(desktop));
  ui.fileListView->header()->hide();

  // http://doc.qt.io/qt-5/signalsandslots.html
  connect(ui.dirTreeView->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          &MainWindow::OnDirectoryChanged);

  connect(ui.fileListView->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          &MainWindow::OnFileSelected);

  // Ukrywa niepotrzebne kolumny.
  for (int nCount = 1; nCount < dirTreeModel->columnCount(); nCount++)
    ui.dirTreeView->hideColumn(nCount);

  for (int nCount = 1; nCount < fileListModel->columnCount(); nCount++)
    ui.fileListView->hideColumn(nCount);
}

void MainWindow::OnDirectoryChanged(const QItemSelection &selected,
                                    const QItemSelection &deselected) const {
  auto index = selected.indexes().first();

  fileListModel->setRootPath(dirTreeModel->filePath(index) + "/");
  ui.fileListView->setRootIndex(
      fileListModel->index(dirTreeModel->filePath(index) + "/"));
}

void MainWindow::OnFileSelected(const QItemSelection &selected,
                                const QItemSelection &deselected) {
  if (imageEditor != nullptr) {
    delete imageEditor;
    imageEditor = nullptr; // Ważne.
  }

  try {
    auto index = selected.indexes().first();
    imageEditor = new ImageEditor(fileListModel->filePath(index));
  } catch (int code) {
    return;
  }

  imageEditor->rubberBand.MousePositionTracker =
      std::bind(&MainWindow::OnMouseMove, this, std::placeholders::_1);
  ;
  imageEditor->rubberBand.SelectionTracker =
      std::bind(&MainWindow::OnSelectionDrag, this, std::placeholders::_1);
  ;
  imageEditor->rubberBand.WheelTracker =
      std::bind(&MainWindow::OnMouseWheel, this, std::placeholders::_1,
                std::placeholders::_2);
  ;

  ui.imagePreview->setScene(imageEditor->previewScene);
  ui.actionSaveAs->setEnabled(true);

  FitPreviewToWindow();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  if (ui.actionFitWindow->isChecked())
    FitPreviewToWindow();
}

void MainWindow::FitPreviewToWindow() const {
  if (imageEditor == nullptr)
    return;
  if (!ui.actionFitWindow->isChecked())
    return;

  imageEditor->SetMaxPreviewSize(ui.imagePreview->width() - 2 - 15,
                                 ui.imagePreview->height() - 2 - 15);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << event->pos();
}

/**
 * @brief Otwiera okno dialogowe służące zapisowi obrazu do nowej lokalizacji.
 */
void MainWindow::OnSaveAs() {
  QString filters;
  auto first = true;

  // Wczytuje listę dostępnych formatów plików.
  for (auto format : QImageWriter::supportedImageFormats()) {
    if (first)
      first = false;
    else
      filters += ";;";
    filters += QString(format).toUpper() + " (*." + format + ")";
  }

  // Zapis domyślnie na pulpicie.
  auto desktop =
      QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)
          .first();
  auto fileName =
      QFileDialog::getSaveFileName(this, "Zapisz plik", desktop, filters);

  if (imageEditor == nullptr)
    return;
  imageEditor->SaveToFile(fileName);
}

/**
 * @brief Powiększa podgląd obrazu.
 */
void MainWindow::OnZoomIn() const {
  if (imageEditor == nullptr)
    return;

  if (ui.actionFitWindow->isChecked())
    ui.actionFitWindow->setChecked(false);

  imageEditor->SetPreviewZoom(imageEditor->PreviewZoom() * 2);
}

/**
 * @brief Zmniejsza podgląd obrazu.
 */
void MainWindow::OnZoomOut() const {
  if (imageEditor == nullptr)
    return;

  if (ui.actionFitWindow->isChecked())
    ui.actionFitWindow->setChecked(false);

  imageEditor->SetPreviewZoom(imageEditor->PreviewZoom() / 2);
}

/**
 * @brief Powiększa lub zmniejsza podgląd obrazu w reakcji na zdarzenie
 * pokręcenia rolką myszy.
 */
void MainWindow::OnMouseWheel(int delta, QPoint localPos) const {
  if (imageEditor == nullptr)
    return;

  if (ui.actionFitWindow->isChecked())
    ui.actionFitWindow->setChecked(false);

  auto oldZoom = imageEditor->PreviewZoom();
  auto newZoom = oldZoom + (delta / 120.0) * 0.05;
  imageEditor->SetPreviewZoom(newZoom <= 0 ? oldZoom : newZoom);
}

/**
 * @brief Dopasowuje podgląd obrazu do rozmiaru okna.
 */
void MainWindow::OnFitWindow() const { FitPreviewToWindow(); }

/**
 * @brief Ustawia rozmiar podglądu na rzeczywiste wymiary obrazu.
 */
void MainWindow::OnFitActual() const {
  if (imageEditor == nullptr)
    return;

  if (ui.actionFitWindow->isChecked())
    ui.actionFitWindow->setChecked(false);

  imageEditor->SetPreviewZoom(1);
}

/**
 * @brief Obraca obraz o 90 stopni w lewo.
 */
void MainWindow::OnRotateLeft() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->Rotate(-90);
  FitPreviewToWindow();
}

/**
 * @brief Obraca obraz o 90 stopni w prawo.
 */
void MainWindow::OnRotateRight() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->Rotate(90);
  FitPreviewToWindow();
}

/**
 * @brief Otwiera okienko dialogowe z informacjami o programie.
 */
void MainWindow::OnAbout() {
  auto dialog = new QDialog(this);
  // Ukrywa przycisk pomocy z paska tytułowego.
  dialog->setWindowFlags(dialog->windowFlags() &
                         ~Qt::WindowContextHelpButtonHint);
  Ui::AboutDialog dialogUi;
  dialogUi.setupUi(dialog);
  dialog->show();
}

void MainWindow::OnCrop() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->CropToSelection();
}

void MainWindow::OnConvertToGrayscale() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->ConvertToGrayscale();
}

void MainWindow::OnUndo() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->Undo();
}

void MainWindow::OnRedo() const {
  if (imageEditor == nullptr)
    return;
  imageEditor->Redo();
}

void MainWindow::OnResize() {
  if (imageEditor == nullptr)
    return;

  auto dialog = new QDialog(this);
  // Ukrywa przycisk pomocy z paska tytułowego.
  dialog->setWindowFlags(dialog->windowFlags() &
                         ~Qt::WindowContextHelpButtonHint);
  Ui::ResizeDialog dialogUi;
  dialogUi.setupUi(dialog);

  auto size = imageEditor->Size();
  auto ratio = 1.0 * size.width() / size.height();

  dialogUi.spinBoxPercentage->setValue(100);
  dialogUi.spinBoxWidth->setValue(size.width());
  dialogUi.spinBoxHeight->setValue(size.height());

  connect(dialogUi.spinBoxWidth, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int val) { // Kiedy użytkownik zmienia szerokość, dopasuj
                         // proporcjonalnie wysokość.
            if (!dialogUi.checkBoxRatioLock->isChecked() ||
                !dialogUi.spinBoxWidth->hasFocus())
              return;
            dialogUi.spinBoxHeight->blockSignals(true);
            dialogUi.spinBoxHeight->setValue(dialogUi.spinBoxWidth->value() /
                                             ratio);
            dialogUi.spinBoxHeight->blockSignals(false);
          });

  connect(dialogUi.spinBoxHeight, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int val) { // Kiedy użytkownik zmienia wysokość, dopasuj
                         // proporcjonalnie szerokość.
            if (!dialogUi.checkBoxRatioLock->isChecked() ||
                !dialogUi.spinBoxHeight->hasFocus())
              return;
            dialogUi.spinBoxWidth->setValue(dialogUi.spinBoxHeight->value() *
                                            ratio);
          });

  connect(
      dialogUi.radioButtonPercentageSize, &QRadioButton::toggled,
      [=](bool checked) { dialogUi.spinBoxPercentage->setEnabled(checked); });

  connect(dialogUi.radioButtonAbsoluteSize, &QRadioButton::toggled,
          [=](bool checked) {
            dialogUi.spinBoxWidth->setEnabled(checked);
            dialogUi.spinBoxHeight->setEnabled(checked);
            dialogUi.checkBoxRatioLock->setEnabled(checked);
          });

  auto code = dialog->exec();

  // Użytkownik anulował zmianę rozmiaru.
  if (code == QDialog::Rejected)
    return;

  if (dialogUi.radioButtonPercentageSize->isChecked()) {
    imageEditor->Resize(dialogUi.spinBoxPercentage->value() / 100.0);
  } else if (dialogUi.radioButtonAbsoluteSize->isChecked()) {
    imageEditor->Resize(dialogUi.spinBoxWidth->value(),
                        dialogUi.spinBoxHeight->value());
  }
}

void MainWindow::OnFullScreen() {
  auto makeFullscreen = !isFullScreen();

  ui.dirTreeView->setVisible(!makeFullscreen);
  ui.fileListView->setVisible(!makeFullscreen);
  setWindowState(makeFullscreen ? Qt::WindowFullScreen : Qt::WindowMaximized);
}

void MainWindow::OnMouseMove(QPoint pos) const {
  statusMousePos->setText(
      QString("Mouse position: (%1, %2)").arg(pos.x()).arg(pos.y()).toUtf8());
}

void MainWindow::OnSelectionDrag(QRect rect) const {
  statusSelectionRect->setText(
      QString("Selection coordinates: %1, %2; rectangle size: %3 x %4")
          .arg(rect.x())
          .arg(rect.y())
          .arg(rect.width())
          .arg(rect.height())
          .toUtf8());
}
