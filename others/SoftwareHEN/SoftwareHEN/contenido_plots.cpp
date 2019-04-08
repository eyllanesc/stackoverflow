#include "contenido_plots.h"
#include "ui_contenido_plots.h"

Contenido_PLOTS::Contenido_PLOTS(QWidget *parent)
    : QWidget(parent), ui(new Ui::Contenido_PLOTS) {
  ui->setupUi(this);
  ui->qcustomplot->setVisible(false);
  ui->qcustomplot->setEnabled(false);
  ui->Utext1->setVisible(false);
  ui->Utext2->setVisible(false);
  ui->Utext3->setVisible(false);
  ui->Utext4->setVisible(false);
  ui->Minimun->setVisible(false);
  ui->Maximun->setVisible(false);
  ui->Increment->setVisible(false);
  ui->k->setVisible(false);
  ui->plot_push->setVisible(false);
  ui->holdon_push->setVisible(false);
  ui->export_push->setVisible(false);
}

Contenido_PLOTS::~Contenido_PLOTS() { delete ui; }

void Contenido_PLOTS::on_Uniforme_clicked(bool checked1) { RADIOBUTTONS(); }

void Contenido_PLOTS::on_Diverso_clicked(bool checked2) { RADIOBUTTONS(); }

void Contenido_PLOTS::on_StaticradioButton_clicked(bool checked3) {
  RADIOBUTTONS();
}

void Contenido_PLOTS::on_IncrementradioButton_clicked(bool checked4) {
  RADIOBUTTONS();
}

void Contenido_PLOTS::RADIOBUTTONS() {
  ui->Utext1->setVisible(false);
  ui->Utext2->setVisible(false);
  ui->Utext3->setVisible(false);
  ui->Utext4->setVisible(false);
  ui->Minimun->setVisible(false);
  ui->Maximun->setVisible(false);
  ui->Increment->setVisible(false);
  ui->k->setVisible(false);
  ui->plot_push->setVisible(false);
  ui->holdon_push->setVisible(false);
  ui->export_push->setVisible(false);
  bool uniforme = ui->Uniforme->isChecked();
  bool diverso = ui->Diverso->isChecked();
  bool estatico = ui->StaticradioButton->isChecked();
  bool incremento = ui->IncrementradioButton->isChecked();
  if (uniforme == true && estatico == true) {
    ui->Utext1->setVisible(true);
    ui->Utext2->setVisible(true);
    ui->Utext3->setVisible(true);
    ui->Utext4->setVisible(false);
    ui->Utext1->setText("Value:");
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(true);
    ui->holdon_push->setVisible(true);
    ui->export_push->setVisible(true);
  } else if (uniforme == true && incremento == true) {
    ui->Utext1->setVisible(true);
    ui->Utext2->setVisible(true);
    ui->Utext3->setVisible(true);
    ui->Utext4->setVisible(false);
    ui->Utext1->setText("Minimun value:");
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(true);
    ui->Increment->setVisible(true);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(true);
    ui->holdon_push->setVisible(true);
    ui->export_push->setVisible(true);
  } else if (diverso == true && estatico == true) {
    ui->Utext1->setVisible(true);
    ui->Utext2->setVisible(true);
    ui->Utext3->setVisible(true);
    ui->Utext4->setVisible(false);
    ui->Utext1->setText("Value:");
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);
    ui->k->setVisible(true);
    ui->plot_push->setVisible(true);
    ui->holdon_push->setVisible(true);
    ui->export_push->setVisible(true);
  } else if (diverso == true && incremento == true) {
    ui->Utext1->setVisible(true);
    ui->Utext2->setVisible(true);
    ui->Utext3->setVisible(true);
    ui->Utext4->setVisible(false);
    ui->Utext1->setText("Minimun value:");
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(true);
    ui->Increment->setVisible(true);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(true);
    ui->holdon_push->setVisible(true);
    ui->export_push->setVisible(true);
  } else if (uniforme == false || diverso == false) {
    ui->Utext1->setVisible(false);
    ui->Utext2->setVisible(false);
    ui->Utext3->setVisible(false);
    ui->Utext4->setVisible(false);
    ui->Minimun->setVisible(false);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(false);
    ui->holdon_push->setVisible(false);
    ui->export_push->setVisible(false);
  }
}

void Contenido_PLOTS::on_plot_push_clicked(bool checked) {}
