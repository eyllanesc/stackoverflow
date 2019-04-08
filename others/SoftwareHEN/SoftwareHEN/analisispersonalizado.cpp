#include "analisispersonalizado.h"
#include "ui_analisispersonalizado.h"
#include <QMessageBox>

AnalisisPersonalizado::AnalisisPersonalizado(QWidget *parent)
    : QWidget(parent), ui(new Ui::AnalisisPersonalizado) {
  ui->setupUi(this);
  // UNIFORME
  ui->Utext9->setVisible(false);
  ui->Utext10->setVisible(false);
  ui->Utext11->setVisible(false);
  ui->Increment->setVisible(false);
  ui->Maximun->setVisible(false);
  ui->Minimun->setVisible(false);
  // DIVERSO
  ui->Dtext4->setVisible(false);
  ui->Dtext5->setVisible(false);
  ui->Dtext6->setVisible(false);
  ui->Dtext7->setVisible(false);
  ui->Dminimun->setVisible(false);
  ui->Dmaximun->setVisible(false);
  ui->Dincrement->setVisible(false);
  ui->Dk->setVisible(false);
  QStringList tituloscapital, titulosoperacion;
  QString titulos;
  tituloscapital << "a"
                 << "b"
                 << "c"
                 << "i"
                 << "n";
  titulosoperacion << "Heating Service"
                   << "Cooling Service";
  titulos = "$$ US/Btu";
  // CHECKBOXES
  ui->UPT->setVisible(false);
  ui->UAP->setVisible(false);
  ui->UCP->setVisible(false);
  ui->UHCC->setVisible(false);
  ui->UCCC->setVisible(false);
  ui->UCC->setVisible(false);
  ui->UCCA->setVisible(false);
  ui->UGCC->setVisible(false);
  ui->UADTM->setVisible(false);
  ui->UCDTM->setVisible(false);
  ui->DPT->setVisible(false);
  ui->DAP->setVisible(false);
  ui->DCP->setVisible(false);
  ui->DHCC->setVisible(false);
  ui->DCCC->setVisible(false);
  ui->DCC->setVisible(false);
  ui->DCCA->setVisible(false);
  ui->DGCC->setVisible(false);
  ui->DADTM->setVisible(false);
  ui->DCDTM->setVisible(false);
  // UNIFORME
  ui->UtableCapital->setColumnCount(5);
  ui->UtableCapital->setHorizontalHeaderLabels(tituloscapital);
  ui->UtableCapital->setItem(0, 0, new QTableWidgetItem("Empty"));
  ui->UtableCapital->setItem(0, 1, new QTableWidgetItem("Empty"));
  ui->UtableCapital->setItem(0, 2, new QTableWidgetItem("Empty"));
  ui->UtableCapital->setItem(0, 3, new QTableWidgetItem("Empty"));
  ui->UtableCapital->setItem(0, 4, new QTableWidgetItem("Empty"));
  ui->UtableOperation->setColumnCount(1);
  ui->UtableOperation->setHorizontalHeaderItem(0,
                                               new QTableWidgetItem(titulos));
  ui->UtableOperation->setVerticalHeaderLabels(titulosoperacion);
  ui->UtableOperation->setItem(0, 0, new QTableWidgetItem("Empty"));
  ui->UtableOperation->setItem(1, 0, new QTableWidgetItem("Empty"));
  // DIVERSO
  ui->DtableCapital->setColumnCount(5);
  ui->DtableCapital->setHorizontalHeaderLabels(tituloscapital);
  ui->DtableCapital->setItem(0, 0, new QTableWidgetItem("Empty"));
  ui->DtableCapital->setItem(0, 1, new QTableWidgetItem(""));
  ui->DtableCapital->setItem(0, 2, new QTableWidgetItem(""));
  ui->DtableCapital->setItem(0, 3, new QTableWidgetItem(""));
  ui->DtableCapital->setItem(0, 4, new QTableWidgetItem(""));
  ui->DtableOperation->setColumnCount(1);
  ui->DtableOperation->setHorizontalHeaderItem(0,
                                               new QTableWidgetItem(titulos));
  ui->DtableOperation->setVerticalHeaderLabels(titulosoperacion);
  ui->DtableOperation->setItem(0, 0, new QTableWidgetItem(""));
  ui->DtableOperation->setItem(1, 0, new QTableWidgetItem(""));
  // a+b*(A)^c
}

AnalisisPersonalizado::~AnalisisPersonalizado() { delete ui; }

void AnalisisPersonalizado::on_StaticradioButton_clicked() {
  botones_uniformes();
}

void AnalisisPersonalizado::on_IncrementradioButton_clicked() {
  botones_uniformes();
}

void AnalisisPersonalizado::on_DStaticradioButton_clicked() {
  botones_diversos();
}

void AnalisisPersonalizado::on_DIncrementradioButton_clicked() {
  botones_diversos();
}

void AnalisisPersonalizado::botones_uniformes() {
  bool incremento = ui->IncrementradioButton->isChecked();
  bool estatico = ui->StaticradioButton->isChecked();
  if (estatico == true) {
    // se borra todo
    ui->Utext9->setVisible(false);
    ui->Utext10->setVisible(false);
    ui->Utext11->setVisible(false);
    ui->Increment->setVisible(false);
    ui->Maximun->setVisible(false);
    ui->Minimun->setVisible(false);
    // CHECBOXES UNIFORME ESTATICO
    ui->UPT->setVisible(false);
    ui->UAP->setVisible(false);
    ui->UCP->setVisible(false);
    ui->UHCC->setVisible(false);
    ui->UCCC->setVisible(false);
    ui->UCC->setVisible(false);
    ui->UCCA->setVisible(false);
    ui->UGCC->setVisible(false);
    ui->UADTM->setVisible(false);
    ui->UCDTM->setVisible(false);
    // se pone CHECBOXES
    ui->UPT->setVisible(true);
    ui->UAP->setVisible(true);
    ui->UCP->setVisible(true);
    ui->UHCC->setVisible(true);
    ui->UCCC->setVisible(true);
    ui->UCC->setVisible(true);
    ui->UCCA->setVisible(true);
    ui->UGCC->setVisible(true);
    //
    ui->Utext9->setVisible(true);
    ui->Utext9->setText("Value:");
    ui->Utext10->setVisible(false);
    ui->Utext11->setVisible(false);
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);

  } else if (incremento == true) {
    // se borra todo
    ui->Utext9->setVisible(false);
    ui->Utext10->setVisible(false);
    ui->Utext11->setVisible(false);
    ui->Increment->setVisible(false);
    ui->Maximun->setVisible(false);
    ui->Minimun->setVisible(false);
    // CHECBOXES UNIFORME INCREMENTO
    ui->UPT->setVisible(false);
    ui->UAP->setVisible(false);
    ui->UCP->setVisible(false);
    ui->UHCC->setVisible(false);
    ui->UCCC->setVisible(false);
    ui->UCC->setVisible(false);
    ui->UCCA->setVisible(false);
    ui->UGCC->setVisible(false);
    ui->UADTM->setVisible(false);
    ui->UCDTM->setVisible(false);
    // se pone CHECKOBEX
    ui->UPT->setVisible(true);
    ui->UAP->setVisible(true);
    ui->UCP->setVisible(true);
    ui->UHCC->setVisible(true);
    ui->UCCC->setVisible(true);
    ui->UCC->setVisible(true);
    ui->UCCA->setVisible(true);
    ui->UGCC->setVisible(true);
    ui->UADTM->setVisible(true);
    ui->UCDTM->setVisible(true);
    //
    ui->Utext9->setVisible(true);
    ui->Utext9->setText("Minimun:");
    ui->Utext10->setVisible(true);
    ui->Utext10->setText("Maximun");
    ui->Utext11->setVisible(true);
    ui->Utext11->setText("Increment");
    ui->Minimun->setVisible(true);
    ui->Maximun->setVisible(true);
    ui->Increment->setVisible(true);
  }
}

void AnalisisPersonalizado::botones_diversos() {
  bool incremento = ui->DIncrementradioButton->isChecked();
  bool estatico = ui->DStaticradioButton->isChecked();
  if (estatico == true) {
    // se borra todo
    ui->Dtext4->setVisible(false);
    ui->Dtext5->setVisible(false);
    ui->Dtext6->setVisible(false);
    ui->Dtext7->setVisible(false);
    ui->Dminimun->setVisible(false);
    ui->Dmaximun->setVisible(false);
    ui->Dincrement->setVisible(false);
    ui->Dk->setVisible(false);
    // CHECBOXES DIVERSOS ESTATICO
    ui->DPT->setVisible(false);
    ui->DAP->setVisible(false);
    ui->DCP->setVisible(false);
    ui->DHCC->setVisible(false);
    ui->DCCC->setVisible(false);
    ui->DCC->setVisible(false);
    ui->DCCA->setVisible(false);
    ui->DGCC->setVisible(false);
    ui->DADTM->setVisible(false);
    ui->DCDTM->setVisible(false);
    // se pone CHEKCBOXES
    ui->DPT->setVisible(true);
    ui->DHCC->setVisible(true);
    ui->DCCC->setVisible(true);
    ui->DCC->setVisible(true);
    ui->DCCA->setVisible(true);
    ui->DGCC->setVisible(true);

    ui->Dtext4->setVisible(true);
    ui->Dtext4->setText("Value:");
    ui->Dminimun->setVisible(true);
    ui->Dk->setVisible(true);
    ui->Dtext7->setVisible(true);
    ui->Dtext7->setText("K");
  } else if (incremento == true) {
    // se borra todo
    ui->Dtext4->setVisible(false);
    ui->Dtext5->setVisible(false);
    ui->Dtext6->setVisible(false);
    ui->Dtext7->setVisible(false);
    ui->Dminimun->setVisible(false);
    ui->Dmaximun->setVisible(false);
    ui->Dincrement->setVisible(false);
    ui->Dk->setVisible(false);
    // CHECKBOXES DIVERSO UNIFORME
    ui->DPT->setVisible(false);
    ui->DAP->setVisible(false);
    ui->DCP->setVisible(false);
    ui->DHCC->setVisible(false);
    ui->DCCC->setVisible(false);
    ui->DCC->setVisible(false);
    ui->DCCA->setVisible(false);
    ui->DGCC->setVisible(false);
    ui->DADTM->setVisible(false);
    ui->DCDTM->setVisible(false);
    // se pone CHECKBOXES
    ui->DPT->setVisible(true);
    ui->DAP->setVisible(true);
    ui->DCP->setVisible(true);
    ui->DHCC->setVisible(true);
    ui->DCCC->setVisible(true);
    ui->DCC->setVisible(true);
    ui->DCCA->setVisible(true);
    ui->DGCC->setVisible(true);
    ui->DADTM->setVisible(true);
    ui->DCDTM->setVisible(true);
    // se pone
    ui->Dtext7->setVisible(true);
    ui->Dtext7->setText("K");
    ui->Dtext4->setVisible(true);
    ui->Dtext4->setText("Minimun:");
    ui->Dtext5->setVisible(true);
    ui->Dtext5->setText("Maximun");
    ui->Dtext6->setVisible(true);
    ui->Dtext6->setText("Increment");
    ui->Dk->setVisible(true);
    ui->Dminimun->setVisible(true);
    ui->Dmaximun->setVisible(true);
    ui->Dincrement->setVisible(true);
  }
}

void AnalisisPersonalizado::on_UAP_clicked() { Ucheckboxes_seleccionadas(); }

void AnalisisPersonalizado::on_UCP_clicked() { Ucheckboxes_seleccionadas(); }

void AnalisisPersonalizado::on_UADTM_clicked() { Ucheckboxes_seleccionadas(); }

void AnalisisPersonalizado::on_UCDTM_clicked() { Ucheckboxes_seleccionadas(); }

void AnalisisPersonalizado::on_DAP_clicked() {}

void AnalisisPersonalizado::on_DCP_clicked() {}

void AnalisisPersonalizado::on_DADTM_clicked() {}

void AnalisisPersonalizado::on_DCDTM_clicked() {}

void AnalisisPersonalizado::Ucheckboxes_seleccionadas() {
  bool SI = ui->StaticradioButton->isChecked();
  bool SIS = ui->IncrementradioButton->isChecked();
  bool uap = ui->UAP->isChecked();
  bool ucp = ui->UCP->isChecked();
  bool uadtm = ui->UADTM->isChecked();
  bool ucdtm = ui->UCDTM->isChecked();
  if (SI == true) {
    // aqui se tiene solamente 2 opciones
    if (uap == true && ucp == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && ucp == false) {
      ui->Utext4->setEnabled(true);           // area
      ui->Utext7->setEnabled(true);           // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);     // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    } else if (uap == false && ucp == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && ucp == false) {
      ui->Utext4->setEnabled(false);          // area
      ui->Utext7->setEnabled(false);          // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(false);    // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    }
  } else if (SIS == true) {
    if (uap == true && uadtm == true && ucp == true && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == true && ucp == true && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == false && ucp == true && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == false && ucp == false &&
               ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && uadtm == false && ucp == false &&
               ucdtm == false) {
      ui->Utext4->setEnabled(true);           // area
      ui->Utext7->setEnabled(true);           // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);     // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    } else if (uap == true && uadtm == true && ucp == false && ucdtm == false) {
      ui->Utext4->setEnabled(true);           // area
      ui->Utext7->setEnabled(true);           // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);     // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    } else if (uap == true && uadtm == true && ucp == true && ucdtm == false) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && uadtm == false && ucp == true && ucdtm == false) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && uadtm == false && ucp == false && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == true && ucp == true && ucdtm == false) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == true && ucp == false && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == true && ucp == false &&
               ucdtm == false) {
      ui->Utext4->setEnabled(true);           // area
      ui->Utext7->setEnabled(true);           // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);     // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    } else if (uap == false && uadtm == false && ucp == true &&
               ucdtm == false) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && uadtm == true && ucp == false && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == true && uadtm == false && ucp == true && ucdtm == true) {
      ui->Utext4->setEnabled(true);          // area
      ui->Utext7->setEnabled(true);          // Utext7 type of design
      ui->Utext3->setEnabled(true);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(true);          // Utext6 capital cost
      ui->Utext8->setEnabled(true);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(true);    // type of desing
      ui->UFCapcomboBox->setEnabled(true);   // type costo de capital
      ui->UtableCapital->setEnabled(true);   // tabla de capital
      ui->UtableOperation->setEnabled(true); // tabla de operation
    } else if (uap == false && uadtm == false && ucp == false &&
               ucdtm == false) {
      ui->Utext4->setEnabled(false);          // area
      ui->Utext7->setEnabled(false);          // Utext7 type of design
      ui->Utext3->setEnabled(false);          // Utext3 cost requiremente
      ui->Utext6->setEnabled(false);          // Utext6 capital cost
      ui->Utext8->setEnabled(false);          // Utext8 operation cost
      ui->UTodcomboBox->setEnabled(false);    // type of desing
      ui->UFCapcomboBox->setEnabled(false);   // type costo de capital
      ui->UtableCapital->setEnabled(false);   // tabla de capital
      ui->UtableOperation->setEnabled(false); // tabla de operation
    }
  }
}
