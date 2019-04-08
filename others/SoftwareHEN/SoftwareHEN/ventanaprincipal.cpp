#include "ventanaprincipal.h"
#include "analisispersonalizado.h"
#include "duvaloraction.h"
#include "plots.h"
#include "summary.h"
#include "tabladatos.h"
#include "ui_ventanaprincipal.h"
#include "unidadesentrada.h"
#include "valoraction.h"
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QStandardItem>
#include <QTextStream>
#include <QtCore>
#include <QtGui>

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VentanaPrincipal) {
  ui->setupUi(this);
  setCentralWidget(ui->mdiArea);
  setWindowTitle("Software Heat Exchanger Network ");
  loadSubWindowPrincipal(new UnidadesEntrada(this));

  // connect(ui->actionNew,SIGNAL(triggered(bool)),this,SIGNAL(actionNewAC(int)));
  // connect(ui->actionNew,SIGNAL(),this,SLOT());
  // connect(ui)
}

VentanaPrincipal::~VentanaPrincipal() { delete ui; }

void VentanaPrincipal::loadSubWindow(QWidget *widget, int ValorACTION) {
  QString Titulo, RutaIcono;
  if (ValorACTION == 1) { // NEW
    Titulo = "WorkSpace";
    RutaIcono = ":/resources/Resources/workspace.png";
  } else if (ValorACTION == 2) { // OPEN
    Titulo = "WorkSpace";
    RutaIcono = ":/resources/Resources/workspace.png";
  } else if (ValorACTION == 3) { // CUSTOM ANALISYS
    Titulo = "Custom analisys";
    RutaIcono = "";
  } else if (ValorACTION == 4) { // GRAFICOS
    Titulo = "Plots";
    RutaIcono = ":/resources/Resources/plots.png";
  } else if (ValorACTION == 5) { // SUMMARY
    Titulo = "Report Options";
    RutaIcono = "";
  }
  auto window = ui->mdiArea->addSubWindow(widget);
  window->setWindowTitle(Titulo);
  window->setWindowIcon(QIcon(RutaIcono));
  window->show();
}

void VentanaPrincipal::loadSubWindowPrincipal(QWidget *widget) {
  int x, y, w, h;
  x = geometry().x() / 2;
  y = geometry().y() / 2;
  w = widget->sizeHint().width() + 30;
  h = widget->sizeHint().height() + 30;
  QString Titulo, RutaIcono;
  Titulo = "Welcome";
  RutaIcono = "";
  auto window = ui->mdiArea->addSubWindow(widget);
  window->setWindowTitle(Titulo);
  window->setWindowIcon(QIcon(RutaIcono));
  window->setGeometry(x, y, w, h);
  window->show();
}

void VentanaPrincipal::on_actionNew_triggered() // NEW
{ // se tiene que abrir de TablaDatos
  int ValorACTION = 1;
  QFile F(VALORACTION_FILENAME);
  if (!F.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "error", F.errorString());
    return;
  }
  QDataStream out(&F);
  out.setVersion(QDataStream::Qt_5_4);
  Duvaloraction valoraction(ValorACTION);
  out << valoraction;
  F.flush();
  F.close();
  loadSubWindow(new TablaDatos(this), ValorACTION);
}

void VentanaPrincipal::on_actionOpen_triggered() {
  int ValorACTION = 2;
  QFile F(VALORACTION_FILENAME);
  if (!F.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "error", F.errorString());
    return;
  }
  QDataStream out(&F);
  out.setVersion(QDataStream::Qt_5_4);
  Duvaloraction valoraction(ValorACTION);
  out << valoraction;
  F.flush();
  F.close();
  loadSubWindow(new TablaDatos(this), ValorACTION);
}

void VentanaPrincipal::on_actionSave_triggered() {
  // conectar con la ventana tablas save
}

void VentanaPrincipal::on_actionSave_as_triggered() {
  // conectar con la ventana tablas save as
}

void VentanaPrincipal::on_actionClose_triggered() { close(); }

void VentanaPrincipal::on_actionCustom_Analysis_triggered() {
  int ValorACTION = 3;
  loadSubWindow(new AnalisisPersonalizado(this), ValorACTION);
}

void VentanaPrincipal::on_actionPlots_triggered() {
  int ValorACTION = 4;
  loadSubWindow(new plots(this), ValorACTION);
}

void VentanaPrincipal::on_actionReport_Options_triggered() {
  int ValorACTION = 5;
  loadSubWindow(new Summary(this), ValorACTION);
}
