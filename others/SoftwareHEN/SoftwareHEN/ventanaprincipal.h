#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H
#include "tabladatos.h"
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QtCore>
#include <QtGui>

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow {
  Q_OBJECT

public:
  explicit VentanaPrincipal(QWidget *parent = 0);
  ~VentanaPrincipal();
  TablaDatos *tabladatos;

private:
  void loadSubWindow(QWidget *widget, int ValorACTION);
  void loadSubWindowPrincipal(QWidget *widget);
  Ui::VentanaPrincipal *ui;

public slots:

private slots:
  void on_actionNew_triggered();
  void on_actionOpen_triggered();
  void on_actionSave_triggered();
  void on_actionSave_as_triggered();
  void on_actionClose_triggered();
  void on_actionCustom_Analysis_triggered();

  void on_actionPlots_triggered();

  void on_actionReport_Options_triggered();

signals:
  void actionNew(int ValorTabla);
};

#endif // VENTANAPRINCIPAL_H
