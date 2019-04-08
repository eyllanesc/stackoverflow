#include "plots.h"
#include "QDataStream"
#include "QFile"
#include "QMessageBox"
#include "contenido_plots.h"
#include "duvaloraction.h"
#include "ui_plots.h"
plots::plots(QWidget *parent) : QWidget(parent), ui(new Ui::plots) {
  ui->setupUi(this);
  QFile F(TYPEOPERATION_FILENAME);
  if (!F.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QDataStream in(&F);
  in.setVersion(QDataStream::Qt_5_4);
  Valordeoperacion valor;
  while (!in.atEnd()) {
    in >> valor;
    if (valor.getvalor() == 0) { // NEW
      // aqui no se hace nada no se tiene nada de nada
    } else if (valor.getvalor() == 1) {
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Compositives curves "));
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Compositives curves adjusted "));
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Grand compositive curve "));
    } else {
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Compositives curves "));
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Compositives curves adjusted "));
      ui->tabWidget->addTab(new Contenido_PLOTS(),
                            QString("Grand compositive curve "));
      ui->tabWidget->addTab(new QWidget(), QString("Area curve "));
      ui->tabWidget->addTab(new QWidget(), QString("Cost curve "));
    }
  }
  F.close();
  //
  QFile Fil(TABPLOT_FILENAME);
  if (!Fil.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QDataStream out(&Fil);
  out.setVersion(QDataStream::Qt_5_4);
  Tabplot tabvalue;
  tabvalue.settabvalue(1);
  out << tabvalue;
  Fil.flush();
  Fil.close();
}

plots::~plots() { delete ui; }

void plots::on_tabWidget_currentChanged(int index) {
  QFile F(TABPLOT_FILENAME);
  if (!F.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QDataStream out(&F);
  out.setVersion(QDataStream::Qt_5_4);
  Tabplot tabvalue(index);
  out << tabvalue;
  F.flush();
  F.close();
}
