#pragma once

#include "ImageEditor.h"
#include "ui_MainWindow.h"
#include <QFileSystemModel>
#include <QLabel>
#include <QMainWindow>

class QItemSelection;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void OnDirectoryChanged(const QItemSelection &selected,
                          const QItemSelection &deselected) const;
  void OnFileSelected(const QItemSelection &selected,
                      const QItemSelection &deselected);
  void OnSaveAs();
  void OnZoomIn() const;
  void OnZoomOut() const;
  void OnFitWindow() const;
  void OnFitActual() const;
  void OnRotateLeft() const;
  void OnRotateRight() const;
  void OnAbout();
  void OnCrop() const;
  void OnConvertToGrayscale() const;
  void OnUndo() const;
  void OnRedo() const;
  void OnResize();
  void OnFullScreen();

protected:
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  void OnMouseMove(QPoint pos) const;
  void OnSelectionDrag(QRect rect) const;
  void OnMouseWheel(int delta, QPoint localPos) const;

  Ui::MainWindow ui;
  QFileSystemModel *dirTreeModel;
  QFileSystemModel *fileListModel;
  void SetupFileBrowser();
  ImageEditor *imageEditor = nullptr;

  QLabel *statusMousePos = new QLabel();
  QLabel *statusSelectionRect = new QLabel();

  void FitPreviewToWindow() const;
};
