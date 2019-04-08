#include "tabladatos.h"
#include "duvaloraction.h"
#include "ui_tabladatos.h"
#include "valoraction.h"
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QVector>

TablaDatos::TablaDatos(QWidget *parent)
    : QWidget(parent), ui(new Ui::TablaDatos) {
  ui->setupUi(this);
  // TREEVIEW
  dirmodel = new QFileSystemModel(this);
  dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
  dirmodel->setRootPath(QDir::rootPath());
  ui->treeView->setModel(dirmodel);
  // LISTVIEW
  filemodel = new QFileSystemModel(this);
  filemodel->setFilter((QDir::NoDotAndDotDot | QDir::Files));
  filemodel->setRootPath(QDir::rootPath());
  ui->listView->setModel(filemodel);
  QFile F(VALORACTION_FILENAME);
  if (!F.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QDataStream in(&F);
  in.setVersion(QDataStream::Qt_5_4);
  Duvaloraction valoraction;
  while (!in.atEnd()) {
    in >> valoraction;
    int accion = valoraction.getvalact();
    if (valoraction.getvalact() == 1) { // NEW
      INICIO(accion, 0);
    } else if (valoraction.getvalact() == 2) { // OPEN
      // CARGAR ACCIÓN DE ABRIR
      // ABRIR ARCHIVO .CSV
      QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
      QFile file(file_name);
      file_path = file_name;
      if (file_path.contains(".csv")) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
          //                    int lineindex=0;
          int Properties;
          int contadorlines = 1; // file line counter
          QTextStream in(&file);
          QStringList Almacenador;
          // ui->Workspace->setRowCount(lineindex);
          while (!in.atEnd()) {
            if (contadorlines == 1) {
              QString fileLine = in.readLine();
              QStringList lineToken =
                  fileLine.split(",", QString::SkipEmptyParts);
              QString analisis = lineToken.at(0);
              int ANALISIS = analisis.toInt();
              if (ANALISIS == 1) { // regresa tabla problema
                Properties = 3;
              } else if (ANALISIS >= 2) {
                Properties = 4;
              }
              INICIO(accion, ANALISIS);
              ui->TypeAnalysis->setCurrentIndex(ANALISIS);
            } else if (contadorlines ==
                       2) { // se lee el tipo de sistema de unideade
              QString fileLine = in.readLine();
              QStringList lineToken =
                  fileLine.split(",", QString::SkipEmptyParts);
              QString Si = lineToken.at(0);  //
              QString Sis = lineToken.at(1); //
              QStringList Lista1, Lista2, Lista3;
              int SI = Si.toInt();
              int SIS = Sis.toInt();
              if (SI == 1) {
                ui->SIradioButton->setAutoExclusive(false);
                ui->SIradioButton->setChecked(true);
                ui->SIradioButton->setAutoExclusive(true);
                ui->SISradioButton->setAutoExclusive(false);
                ui->SISradioButton->setChecked(false);
                ui->SISradioButton->setAutoExclusive(true);
                Lista1 << "Select one..."
                       << "Kelvin (°K)"
                       << "Farenheit (°F)"
                       << "Celsius (°C)"
                       << "Ranking (°R)";
                Lista2 << "Select one..."
                       << "Btu/hr ft^2 °F"
                       << "CHU/hr ft^2 °F";
                Lista3 << "Select one..."
                       << "Btu/hr °F'"
                       << "Btu/min °F"
                       << "Btu/seg °F"
                       << "Btu/hr °C"
                       << "Btu/min °C"
                       << "Btu/seg °C"
                       << "Btu/hr °R"
                       << "Btu/min °R"
                       << "Btu/seg °R";
              } else if (SIS == 1) {
                ui->SIradioButton->setAutoExclusive(false);
                ui->SIradioButton->setChecked(false);
                ui->SIradioButton->setAutoExclusive(true);
                ui->SISradioButton->setAutoExclusive(false);
                ui->SISradioButton->setChecked(true);
                ui->SISradioButton->setAutoExclusive(true);
                Lista1 << "Select one..."
                       << "Kelvin (°K)"
                       << "Farenheit (°F)"
                       << "Celsius (°C)"
                       << "Ranking (°R)";
                Lista2 << "Select one..."
                       << "W/m^2 °K"
                       << "W/m^2 °C";
                Lista3 << "Select one..."
                       << "Joules/hr °K"
                       << "Joules/min °K"
                       << "Joules/seg °K"
                       << "Joules/hr °C"
                       << "Joules/min °C"
                       << "Joules/seg °C"
                       << "KiloJoules/hr °K"
                       << "KiloJoules/min °K"
                       << "KiloJoules/seg °K"
                       << "KiloJoules/hr °C"
                       << "KiloJoules/min °C"
                       << "KiloJoules/seg °C"
                       << "KiloCal/hr °C"
                       << "KiloCal/min °C"
                       << "KiloCal/seg °C";
              }
              if (Properties == 3) { // T,WCP
                ui->TcomboBox->setVisible(true);
                ui->WcomboBox->setVisible(true);
                ui->TcomboBox->clear();
                ui->WcomboBox->clear();
                ui->TcomboBox->addItems(Lista1);
                ui->WcomboBox->addItems(Lista3);
                ui->label_2->setVisible(true);
                ui->label_4->setVisible(true);
              } else if (Properties == 4) { // T,WCP y H
                ui->TcomboBox->setVisible(true);
                ui->WcomboBox->setVisible(true);
                ui->FcomboBox->setVisible(true);
                ui->TcomboBox->clear();
                ui->FcomboBox->clear();
                ui->WcomboBox->clear();
                ui->TcomboBox->addItems(Lista1);
                ui->FcomboBox->addItems(Lista2);
                ui->WcomboBox->addItems(Lista3);
                ui->label_2->setVisible(true);
                ui->label_3->setVisible(true);
                ui->label_4->setVisible(true);
              }
            } else if (contadorlines == 3) {
              if (Properties == 3) {
                QString fileLine = in.readLine();
                QStringList lineToken =
                    fileLine.split(",", QString::SkipEmptyParts);
                QString Tunidades = lineToken.at(0); //
                QString Wunidades = lineToken.at(1); //
                int TUNIDADES = Tunidades.toInt();
                int WUNIDADES = Wunidades.toInt();
                ui->TcomboBox->setCurrentIndex(TUNIDADES);
                ui->WcomboBox->setCurrentIndex(WUNIDADES);
              } else if (Properties == 4) {
                QString fileLine = in.readLine();
                QStringList lineToken =
                    fileLine.split(",", QString::SkipEmptyParts);
                QString Tunidades = lineToken.at(0); //
                QString Wunidades = lineToken.at(1); //
                QString Funidades = lineToken.at(2);
                int TUNIDADES = Tunidades.toInt();
                int WUNIDADES = Wunidades.toInt();
                int FUNIDADES = Funidades.toInt();
                ui->TcomboBox->setCurrentIndex(TUNIDADES);
                ui->WcomboBox->setCurrentIndex(WUNIDADES);
                ui->FcomboBox->setCurrentIndex(FUNIDADES);
              }
            } else if (contadorlines >= 4) {
              QString fileLine = in.readLine();
              QStringList lineToken =
                  fileLine.split(",", QString::SkipEmptyParts);
              Almacenador.append(lineToken);
            }
            contadorlines++;
          }
          file.close();
          QVector<QString> vec;
          qDebug() << Almacenador;
          foreach (QString str, Almacenador) { vec.push_back(str); }
          /*qDebug() << vec;
          qDebug() << vec[0];*/
          // qDebug() << Almacenador[0][1];
          // QString value = "Empty";
          // qDebug() << value;
          int filas = Almacenador.size() / Properties;
          int columnas = Properties;
          qDebug() << filas;
          qDebug() << columnas;

          disconnect(ui->Workspace, SIGNAL(cellChanged(int, int)), 0,
                     0); // &TablaDatos::on_Workspace_cellChanged);

          ui->Workspace->setRowCount(filas);
          ui->Workspace->setColumnCount(columnas);
          int h = 0;

          for (int r = 0; r < ui->Workspace->rowCount(); r++) {
            for (int c = 0; c < ui->Workspace->columnCount(); c++) {
              QString value = Almacenador.at(h);
              h++;
              qDebug() << "values" << r << c << value;
              ui->Workspace->setItem(r, c, new QTableWidgetItem(value));
              // ui->Workspace->setItem(r,c,new QTableWidgetItem (value));
            }
          }
          connect(ui->Workspace, &QTableWidget::cellChanged, this,
                  &TablaDatos::on_Workspace_cellChanged);
        }
      }
    }
    F.close();
    file_path = ""; // CORREGIR;
    BORRARFILA = -1;
  }
}

TablaDatos::~TablaDatos() { delete ui; }

void TablaDatos::on_Addcorrientes_clicked() {
  int Analisis = ui->TypeAnalysis->currentIndex();
  int NumCorri = ui->NumeroCorrientes->value();
  int TempU = ui->TcomboBox->currentIndex();
  int FilmU = ui->FcomboBox->currentIndex();
  int WcpU = ui->WcomboBox->currentIndex();
  // int wcp = WCP.toInt(), tt = TT.toInt(), to = TO.toInt(), fc=FC.toInt();
  if (Analisis == 0) { // select one
    QMessageBox::warning(this, tr("Error"), tr("Select a type of analysis."));
    return;
  } else if (Analisis == 1) { // tabla problema
    if (TempU == 0 || WcpU == 0) {
      QMessageBox::warning(this, tr("Error"), tr("Missing units."));
      return;
    }
    int data = ui->Workspace->rowCount();
    if (data == 0) {
      ui->Workspace->setRowCount(NumCorri);
      for (int r = 0; r < ui->Workspace->rowCount(); ++r) {
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          ui->Workspace->setItem(r, c, new QTableWidgetItem("Empty"));
        }
      }
    } else {
      ui->Workspace->setRowCount(NumCorri + data);
      for (int r = data; r < ui->Workspace->rowCount(); ++r) {
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          ui->Workspace->setItem(r, c, new QTableWidgetItem("Empty"));
        }
      }
    }
  } else { // area y costos
    if (TempU == 0 || FilmU == 0 || WcpU == 0) {
      QMessageBox::warning(this, tr("Error"), tr("Missing units."));
      return;
    }
    int data = ui->Workspace->rowCount();
    if (data == 0) {
      ui->Workspace->setRowCount(NumCorri);
      for (int r = 0; r < ui->Workspace->rowCount(); ++r) {
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          ui->Workspace->setItem(r, c, new QTableWidgetItem("Empty"));
        }
      }
    } else {
      ui->Workspace->setRowCount(NumCorri + data);
      for (int r = data; r < ui->Workspace->rowCount(); ++r) {
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          ui->Workspace->setItem(r, c, new QTableWidgetItem("Empty"));
        }
      }
    }
  }
}

void TablaDatos::on_SIradioButton_clicked() {
  QStringList Lista1, Lista2, Lista3;
  ui->TcomboBox->clear();
  ui->FcomboBox->clear();
  ui->WcomboBox->clear();
  Lista1 << "Select one..."
         << "Kelvin (°K)"
         << "Farenheit (°F)"
         << "Celsius (°C)"
         << "Ranking (°R)";
  Lista2 << "Select one..."
         << "Btu/hr ft^2 °F"
         << "CHU/hr ft^2 °F";
  Lista3 << "Select one..."
         << "Btu/hr °F'"
         << "Btu/min °F"
         << "Btu/seg °F"
         << "Btu/hr °C"
         << "Btu/min °C"
         << "Btu/seg °C"
         << "Btu/hr °R"
         << "Btu/min °R"
         << "Btu/seg °R";
  int TipoAnalisis = ui->TypeAnalysis->currentIndex();
  if (TipoAnalisis == 0) {
    return;
  } // no se hace seleccionado nada
  else if (TipoAnalisis == 1) {
    ui->TcomboBox->addItems(Lista1);
    ui->WcomboBox->addItems(Lista3);
  } // tabla problema
  else if (TipoAnalisis >= 2) {
    ui->TcomboBox->addItems(Lista1);
    ui->FcomboBox->addItems(Lista2);
    ui->WcomboBox->addItems(Lista3);
  } // costos areas o tros
}

void TablaDatos::on_SISradioButton_clicked() { // corregir
  QStringList Lista1, Lista2, Lista3;
  ui->TcomboBox->clear();
  ui->FcomboBox->clear();
  ui->WcomboBox->clear();
  Lista1 << "Select one..."
         << "Kelvin (°K)"
         << "Farenheit (°F)"
         << "Celsius (°C)"
         << "Ranking (°R)";
  Lista3 << "Select one..."
         << "Joules/hr °K"
         << "Joules/min °K"
         << "Joules/seg °K"
         << "Joules/hr °C"
         << "Joules/min °C"
         << "Joules/seg °C"
         << "KiloJoules/hr °K"
         << "KiloJoules/min °K"
         << "KiloJoules/seg °K"
         << "KiloJoules/hr °C"
         << "KiloJoules/min °C"
         << "KiloJoules/seg °C"
         << "KiloCal/hr °C"
         << "KiloCal/min °C"
         << "KiloCal/seg °C";
  Lista2 << "Select one..."
         << "W/m^2 °K"
         << "W/m^2 °C";
  int TipoAnalisis = ui->TypeAnalysis->currentIndex();
  if (TipoAnalisis == 0) {
    return;
  } // no se hace seleccionado nada
  else if (TipoAnalisis == 1) {
    ui->TcomboBox->addItems(Lista1);
    ui->WcomboBox->addItems(Lista3);
  } // tabla problema
  else if (TipoAnalisis >= 2) {
    ui->TcomboBox->addItems(Lista1);
    ui->FcomboBox->addItems(Lista2);
    ui->WcomboBox->addItems(Lista3);
  } // costos areas o tros
}

void TablaDatos::on_AddnewpushButton_clicked() {
  // corregir
  int NumCorri = ui->Workspace->rowCount();
  int TempU = ui->TcomboBox->currentIndex();
  int FilmU = ui->FcomboBox->currentIndex();
  int WcpU = ui->WcomboBox->currentIndex();
  // int wcp = WCP.toInt(), tt = TT.toInt(), to = TO.toInt(), fc=FC.toInt();
  if (TempU == 0 || FilmU == 0 || WcpU == 0) {
    QMessageBox::warning(this, tr("Error"), tr("Missing units"));
    return;
  }
  ui->Workspace->setRowCount(NumCorri + 1);
}

void TablaDatos::on_SavepushButton_clicked() // SAVE
{
  // ACCION DE GUARDAR ARCHIVO .CSV
  if (file_path == "") { // es decir no se ha guardado entonces se tiene guardar
                         // por primera vez
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    QFile csvFile(file_name + ".csv");
    file_path = file_name;
    if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
      QTextStream data(&csvFile);
      QStringList strList;
      int Analisis = ui->TypeAnalysis->currentIndex();
      int Tcombo = ui->TcomboBox->currentIndex();
      int Wcombo = ui->WcomboBox->currentIndex();
      int Fcombo = ui->FcomboBox->currentIndex();
      bool SI = ui->SIradioButton->isChecked();
      bool SIS = ui->SISradioButton->isChecked();
      QString TCOMBO = QString::number(Tcombo);
      QString WCOMBO = QString::number(Wcombo);
      QString FCOMBO = QString::number(Fcombo);
      QString MSI = QString::number(SI);
      QString MSIS = QString::number(SIS);
      QString ANALISIS = QString::number(Analisis);
      if (Analisis == 0) { // selecc one
        return;
      } else if (Analisis == 1) { // tabla problema
        strList << ANALISIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << MSI;
        strList << MSIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << TCOMBO;
        strList << WCOMBO;
        data << strList.join(",") + "\n";
      } else if (Analisis >= 2) { // ara
        strList << ANALISIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << MSI;
        strList << MSIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << TCOMBO;
        strList << WCOMBO;
        strList << FCOMBO;
        data << strList.join(",") + "\n";
      }
      strList.clear();
      for (int r = 0; r < ui->Workspace->rowCount(); ++r) {
        strList.clear();
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          QTableWidgetItem *item = ui->Workspace->item(r, c); // Load items
          if (!item ||
              item->text().isEmpty()) // Test if there is something at item(r,c)
          {
            ui->Workspace->setItem(
                r, c, new QTableWidgetItem("0")); // IF there is nothing write 0
          }
          strList << ui->Workspace->item(r, c)->text();
        }
        data << strList.join(",") + "\n";
      }
      csvFile.close();
    }
  } else {
    QFile csvFile(file_path + ".csv");
    if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
      QTextStream data(&csvFile);
      QStringList strList;
      int Analisis = ui->TypeAnalysis->currentIndex();
      int Tcombo = ui->TcomboBox->currentIndex();
      int Wcombo = ui->WcomboBox->currentIndex();
      int Fcombo = ui->FcomboBox->currentIndex();
      bool SI = ui->SIradioButton->isChecked();
      bool SIS = ui->SISradioButton->isChecked();
      QString TCOMBO = QString::number(Tcombo);
      QString WCOMBO = QString::number(Wcombo);
      QString FCOMBO = QString::number(Fcombo);
      QString MSI = QString::number(SI);
      QString MSIS = QString::number(SIS);
      QString ANALISIS = QString::number(Analisis);
      if (Analisis == 0) { // selecc one
        return;
      } else if (Analisis == 1) { // tabla problema
        strList << ANALISIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << MSI;
        strList << MSIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << TCOMBO;
        strList << WCOMBO;
        data << strList.join(",") + "\n";
      } else if (Analisis >= 2) { // ara
        strList << ANALISIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << MSI;
        strList << MSIS;
        data << strList.join(",") + "\n";
        strList.clear();
        strList << TCOMBO;
        strList << WCOMBO;
        strList << FCOMBO;
        data << strList.join(",") + "\n";
      }
      strList.clear();
      for (int r = 0; r < ui->Workspace->rowCount(); ++r) {
        strList.clear();
        for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
          QTableWidgetItem *item = ui->Workspace->item(r, c); // Load items
          if (!item ||
              item->text().isEmpty()) // Test if there is something at item(r,c)
          {
            ui->Workspace->setItem(
                r, c, new QTableWidgetItem("0")); // IF there is nothing write 0
          }
          strList << ui->Workspace->item(r, c)->text();
        }
        data << strList.join(",") + "\n";
      }
      csvFile.close();
    }
  }
}

void TablaDatos::on_SavepushButton_2_clicked() // SAVE AS
{
  // ACCION DE GUARDAR ARCHIVO .CSV
  QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
  QFile csvFile(file_name + ".csv");
  file_path = file_name;
  if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QTextStream data(&csvFile);
    QStringList strList;
    int Analisis = ui->TypeAnalysis->currentIndex();
    int Tcombo = ui->TcomboBox->currentIndex();
    int Wcombo = ui->WcomboBox->currentIndex();
    int Fcombo = ui->FcomboBox->currentIndex();
    bool SI = ui->SIradioButton->isChecked();
    bool SIS = ui->SISradioButton->isChecked();
    QString TCOMBO = QString::number(Tcombo);
    QString WCOMBO = QString::number(Wcombo);
    QString FCOMBO = QString::number(Fcombo);
    QString MSI = QString::number(SI);
    QString MSIS = QString::number(SIS);
    QString ANALISIS = QString::number(Analisis);
    if (Analisis == 0) { // selecc one
      return;
    } else if (Analisis == 1) { // tabla problema
      strList << ANALISIS;
      data << strList.join(",") + "\n";
      strList.clear();
      strList << MSI;
      strList << MSIS;
      data << strList.join(",") + "\n";
      strList.clear();
      strList << TCOMBO;
      strList << WCOMBO;
      data << strList.join(",") + "\n";
    } else if (Analisis >= 2) { // ara
      strList << ANALISIS;
      data << strList.join(",") + "\n";
      strList.clear();
      strList << MSI;
      strList << MSIS;
      data << strList.join(",") + "\n";
      strList.clear();
      strList << TCOMBO;
      strList << WCOMBO;
      strList << FCOMBO;
      data << strList.join(",") + "\n";
    }
    strList.clear();
    for (int r = 0; r < ui->Workspace->rowCount(); ++r) {
      strList.clear();
      for (int c = 0; c < ui->Workspace->columnCount(); ++c) {
        QTableWidgetItem *item = ui->Workspace->item(r, c); // Load items
        if (!item ||
            item->text().isEmpty()) // Test if there is something at item(r,c)
        {
          ui->Workspace->setItem(
              r, c, new QTableWidgetItem("0")); // IF there is nothing write 0
        }
        strList << ui->Workspace->item(r, c)->text();
      }
      data << strList.join(",") + "\n";
    }
    csvFile.close();
  }
}

void TablaDatos::on_DeleteSelpushButton_clicked() {
  if (BORRARFILA == -1) {
    // NO HAY ITEM SELECCIONADO
  } else {
    ui->Workspace->removeRow(BORRARFILA);
  }
}

void TablaDatos::on_DeleteFirstpushButton_clicked() // BORRAR EL PRIMERO
{
  ui->Workspace->removeRow(0);
}

void TablaDatos::on_DeleteLastpushButton_clicked() {
  ui->Workspace->removeRow(ui->Workspace->rowCount() - 1);
}

void TablaDatos::on_DeleteAllpushButton_clicked() {
  ui->Workspace->setRowCount(0);
}

void TablaDatos::on_Workspace_itemClicked(QTableWidgetItem *item) {
  BORRARFILA = item->row(); // SELECCIONAR FILA A ELIMINAR
}

void TablaDatos::INICIO(int accion, int ANALISIS) {
  if (accion == 1) { // la accion es NEW
    ui->TcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->SIradioButton->setAutoExclusive(false);
    ui->SIradioButton->setChecked(false);
    ui->SIradioButton->setAutoExclusive(true);
    ui->SISradioButton->setAutoExclusive(false);
    ui->SISradioButton->setChecked(false);
    ui->SISradioButton->setAutoExclusive(true);
  } else if (accion == 2) { // la accion es OPEN
    if (ANALISIS == 1) {    // regresa tabla problema
      // Properties = 3;
      ui->TcomboBox->setVisible(true);
      ui->WcomboBox->setVisible(true);
      ui->label_2->setVisible(true);
      ui->label_4->setVisible(true);
    } else if (ANALISIS >= 2) {
      // Properties = 4;
      ui->TcomboBox->setVisible(true);
      ui->FcomboBox->setVisible(true);
      ui->WcomboBox->setVisible(true);
      ui->label_2->setVisible(true);
      ui->label_3->setVisible(true);
      ui->label_4->setVisible(true);
    }
    ui->SIradioButton->setEnabled(true);
    ui->SISradioButton->setEnabled(true);
  }
}

void TablaDatos::actionNewAC() {
  // int val=9;
  // ui->NumeroCorrientes->setValue(val);
  QMessageBox::warning(this, tr("Error"), tr("Missing units"));
}

void TablaDatos::on_TypeAnalysis_currentIndexChanged(int index) {
  // index = ui->TypeAnalysis->currentIndex();
  ui->TcomboBox->clear();
  ui->WcomboBox->clear();
  ui->FcomboBox->clear();
  ui->SIradioButton->setAutoExclusive(false);
  ui->SIradioButton->setChecked(false);
  ui->SIradioButton->setAutoExclusive(true);
  ui->SISradioButton->setAutoExclusive(false);
  ui->SISradioButton->setChecked(false);
  ui->SISradioButton->setAutoExclusive(true);
  if (index == 0) { // select one
    ui->SIradioButton->setEnabled(false);
    ui->SISradioButton->setEnabled(false);
    ui->TcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_3->setVisible(false);
    ui->Workspace->setColumnCount(0);
  } else if (index == 1) { // table problem
    ui->TcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_3->setVisible(false);
    //
    ui->TcomboBox->setVisible(true);
    ui->WcomboBox->setVisible(true);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_3->setVisible(false);
    ui->Workspace->setColumnCount(3);
    titulos.clear();
    titulos << "Supply Temperature"
            << "Target Temperature "
            << "WCp";
    ui->Workspace->setHorizontalHeaderLabels(titulos);
    ui->TcomboBox->addItem("Select a system unit...");
    ui->WcomboBox->addItem("Select a system unit...");
    ui->SIradioButton->setEnabled(true);
    ui->SISradioButton->setEnabled(true);
  } else if (index == 2) { // area prediction
    ui->TcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_3->setVisible(false);
    //
    ui->TcomboBox->setVisible(true);
    ui->WcomboBox->setVisible(true);
    ui->FcomboBox->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_3->setVisible(true);
    ui->Workspace->setColumnCount(4);
    titulos.clear();
    titulos << "Supply Temperature"
            << "Target Temperature "
            << "WCp"
            << "Film Coefficient";
    ui->Workspace->setHorizontalHeaderLabels(titulos);
    ui->TcomboBox->addItem("Select a system unit...");
    ui->FcomboBox->addItem("Select a system unit...");
    ui->WcomboBox->addItem("Select a system unit...");
    ui->SIradioButton->setEnabled(true);
    ui->SISradioButton->setEnabled(true);
  } else if (index == 3) { // cost prediction
    ui->TcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_3->setVisible(false);
    //
    ui->TcomboBox->setVisible(true);
    ui->WcomboBox->setVisible(true);
    ui->FcomboBox->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_3->setVisible(true);
    ui->Workspace->setColumnCount(4);
    titulos.clear();
    titulos << "Supply Temperature"
            << "Target Temperature "
            << "WCp"
            << "Film Coefficient";
    ui->Workspace->setHorizontalHeaderLabels(titulos);
    ui->TcomboBox->addItem("Select a system unit...");
    ui->FcomboBox->addItem("Select a system unit...");
    ui->WcomboBox->addItem("Select a system unit...");
    ui->SIradioButton->setEnabled(true);
    ui->SISradioButton->setEnabled(true);
  } else if (index == 4) { // all

    ui->TcomboBox->setVisible(false);
    ui->WcomboBox->setVisible(false);
    ui->FcomboBox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_3->setVisible(false);
    //
    ui->TcomboBox->setVisible(true);
    ui->WcomboBox->setVisible(true);
    ui->FcomboBox->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_3->setVisible(true);
    ui->Workspace->setColumnCount(4);
    titulos.clear();
    titulos << "Supply Temperature"
            << "Target Temperature "
            << "WCp"
            << "Film Coefficient";
    ui->Workspace->setHorizontalHeaderLabels(titulos);
    ui->TcomboBox->addItem("Select a system unit...");
    ui->FcomboBox->addItem("Select a system unit...");
    ui->WcomboBox->addItem("Select a system unit...");
    ui->SIradioButton->setEnabled(true);
    ui->SISradioButton->setEnabled(true);
  }
  // se guarda la acción
  QFile F(TYPEOPERATION_FILENAME);
  if (!F.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QDataStream out(&F);
  out.setVersion(QDataStream::Qt_5_4);
  Valordeoperacion valor(index);
  out << valor;
  F.flush();
  F.close();
}

void TablaDatos::on_treeView_clicked(const QModelIndex &index) {
  sPath = dirmodel->fileInfo(index).absoluteFilePath();
  ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}

void TablaDatos::on_listView_doubleClicked(const QModelIndex &index) {
  QString file_name = index.data(Qt::DisplayRole).toString();
  QFile file(sPath + "/" + file_name);
  file_path = file_name;
  if (file_path.contains(".csv")) {
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      int lineindex = 0; // file line counter
      QTextStream in(&file);
      // aqui va el ciclo while
      int Properties;
      int contadorlines = 1; // file line counter
      ui->Workspace->setRowCount(0);
      while (!in.atEnd()) {
        if (contadorlines == 1) {
          QString fileLine = in.readLine();
          QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
          QString analisis = lineToken.at(0);
          int ANALISIS = analisis.toInt();
          if (ANALISIS == 1) { // regresa tabla problema
            Properties = 3;
          } else if (ANALISIS >= 2) {
            Properties = 4;
          }
          INICIO(1, ANALISIS);
          ui->TypeAnalysis->setCurrentIndex(ANALISIS);
        } else if (contadorlines ==
                   2) { // se lee el tipo de sistema de unideade
          QString fileLine = in.readLine();
          QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
          QString Si = lineToken.at(0);  //
          QString Sis = lineToken.at(1); //
          QStringList Lista1, Lista2, Lista3;
          int SI = Si.toInt();
          int SIS = Sis.toInt();
          if (SI == 1) {
            ui->SIradioButton->setAutoExclusive(false);
            ui->SIradioButton->setChecked(true);
            ui->SIradioButton->setAutoExclusive(true);
            ui->SISradioButton->setAutoExclusive(false);
            ui->SISradioButton->setChecked(false);
            ui->SISradioButton->setAutoExclusive(true);
            Lista1 << "Select one..."
                   << "Kelvin (°K)"
                   << "Farenheit (°F)"
                   << "Celsius (°C)"
                   << "Ranking (°R)";
            Lista2 << "Select one..."
                   << "Btu/hr ft^2 °F"
                   << "CHU/hr ft^2 °F";
            Lista3 << "Select one..."
                   << "Btu/hr °F'"
                   << "Btu/min °F"
                   << "Btu/seg °F"
                   << "Btu/hr °C"
                   << "Btu/min °C"
                   << "Btu/seg °C"
                   << "Btu/hr °R"
                   << "Btu/min °R"
                   << "Btu/seg °R";
          } else if (SIS == 1) {
            ui->SIradioButton->setAutoExclusive(false);
            ui->SIradioButton->setChecked(false);
            ui->SIradioButton->setAutoExclusive(true);
            ui->SISradioButton->setAutoExclusive(false);
            ui->SISradioButton->setChecked(true);
            ui->SISradioButton->setAutoExclusive(true);
            Lista1 << "Select one..."
                   << "Kelvin (°K)"
                   << "Farenheit (°F)"
                   << "Celsius (°C)"
                   << "Ranking (°R)";
            Lista2 << "Select one..."
                   << "W/m^2 °K"
                   << "W/m^2 °C";
            Lista3 << "Select one..."
                   << "Joules/hr °K"
                   << "Joules/min °K"
                   << "Joules/seg °K"
                   << "Joules/hr °C"
                   << "Joules/min °C"
                   << "Joules/seg °C"
                   << "KiloJoules/hr °K"
                   << "KiloJoules/min °K"
                   << "KiloJoules/seg °K"
                   << "KiloJoules/hr °C"
                   << "KiloJoules/min °C"
                   << "KiloJoules/seg °C"
                   << "KiloCal/hr °C"
                   << "KiloCal/min °C"
                   << "KiloCal/seg °C";
          }
          if (Properties == 3) { // T,WCP
            ui->TcomboBox->setVisible(true);
            ui->WcomboBox->setVisible(true);
            ui->TcomboBox->clear();
            ui->WcomboBox->clear();
            ui->TcomboBox->addItems(Lista1);
            ui->WcomboBox->addItems(Lista3);
            ui->label_2->setVisible(true);
            ui->label_4->setVisible(true);
          } else if (Properties == 4) { // T,WCP y H
            ui->TcomboBox->setVisible(true);
            ui->WcomboBox->setVisible(true);
            ui->FcomboBox->setVisible(true);
            ui->TcomboBox->clear();
            ui->FcomboBox->clear();
            ui->WcomboBox->clear();
            ui->TcomboBox->addItems(Lista1);
            ui->FcomboBox->addItems(Lista2);
            ui->WcomboBox->addItems(Lista3);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->label_4->setVisible(true);
          }
        } else if (contadorlines == 3) {
          if (Properties == 3) {
            QString fileLine = in.readLine();
            QStringList lineToken =
                fileLine.split(",", QString::SkipEmptyParts);
            QString Tunidades = lineToken.at(0); //
            QString Wunidades = lineToken.at(1); //
            int TUNIDADES = Tunidades.toInt();
            int WUNIDADES = Wunidades.toInt();
            ui->TcomboBox->setCurrentIndex(TUNIDADES);
            ui->WcomboBox->setCurrentIndex(WUNIDADES);
          } else if (Properties == 4) {
            QString fileLine = in.readLine();
            QStringList lineToken =
                fileLine.split(",", QString::SkipEmptyParts);
            QString Tunidades = lineToken.at(0); //
            QString Wunidades = lineToken.at(1); //
            QString Funidades = lineToken.at(2);
            int TUNIDADES = Tunidades.toInt();
            int WUNIDADES = Wunidades.toInt();
            int FUNIDADES = Funidades.toInt();
            ui->TcomboBox->setCurrentIndex(TUNIDADES);
            ui->WcomboBox->setCurrentIndex(WUNIDADES);
            ui->FcomboBox->setCurrentIndex(FUNIDADES);
          }
        } else if (contadorlines > 3) {
          ui->Workspace->insertRow(ui->Workspace->rowCount());
          QString fileLine = in.readLine();
          QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
          ui->Workspace->setColumnCount(lineToken.size());
          for (int j = 0; j < lineToken.size(); j++) {
            QString value = lineToken.at(j);
            ui->Workspace->setItem(lineindex, j, new QTableWidgetItem(value));
          }
          lineindex++;
        }
        contadorlines++;
      }
      file.close();
    }
  }
}

void TablaDatos::on_UploadExistinpushButton_clicked() {
  QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
  // ui->label->setText(file_name);
  QFile file(file_name);
  file_path = file_name;
  if (file_path.contains(".csv")) {
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream in(&file);
      int contadorlines = 0;
      int lineindex = ui->Workspace->rowCount();
      while (!in.atEnd()) {
        if (contadorlines < 3) {
          QString fileLine = in.readLine();
        } else if (contadorlines > 3) {
          ui->Workspace->insertRow(ui->Workspace->rowCount());
          QString fileLine = in.readLine();
          QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
          int ColumAct = ui->Workspace->columnCount();
          int ColumDes = lineToken.size();
          if (ColumAct == 3 && ColumDes == 3) {
            ui->Workspace->setColumnCount(ColumAct);
            titulos.clear();
            titulos << "Supply Temperature"
                    << "Target Temperature "
                    << "WCp";
            ui->Workspace->setHorizontalHeaderLabels(titulos);
          } else if (ColumAct == 4 && ColumDes == 3) {
            ui->Workspace->setColumnCount(ColumAct);
            titulos.clear();
            titulos << "Supply Temperature"
                    << "Target Temperature "
                    << "WCp";
            ui->Workspace->setHorizontalHeaderLabels(titulos);
          } else if (ColumAct == 3 && ColumDes == 4) {
            ui->Workspace->setColumnCount(ColumDes);
            titulos.clear();
            titulos << "Supply Temperature"
                    << "Target Temperature "
                    << "WCp"
                    << "Film Coefficient";
            ui->Workspace->setHorizontalHeaderLabels(titulos);
          } else if (ColumAct == 4 && ColumDes == 4) {
            ui->Workspace->setColumnCount(ColumDes);
            titulos.clear();
            titulos << "Supply Temperature"
                    << "Target Temperature "
                    << "WCp"
                    << "Film Coefficient";
            ui->Workspace->setHorizontalHeaderLabels(titulos);
          }
          for (int j = 0; j < lineToken.size(); j++) {
            QString value = lineToken.at(j);
            ui->Workspace->setItem(lineindex, j, new QTableWidgetItem(value));
          }
          lineindex++;
        }
        contadorlines++;
      }
      file.close();
    }
  }
}

void TablaDatos::on_Workspace_cellChanged(int row, int column) {

  int r = ui->Workspace->rowCount();
  int c = ui->Workspace->columnCount();
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      // if(!ui->Workspace->item(i, j))
      if (ui->Workspace->item(i, j)->text() == "Empty") {
        return;
      } else if (ui->Workspace->item(i, j)->text() == "0") {
        return;
      }
    }
  }
  QFile F(WORKSPACE_FILENAME);
  if (!F.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Error"), tr("Nada no pasa nada"));
    return;
  }
  QVector<QVector<double>> WORKSPACE_matrix;
  row = ui->Workspace->rowCount();
  column = ui->Workspace->columnCount();
  WORKSPACE_matrix.resize(row);
  for (int i = 0; i < row; i++) {
    WORKSPACE_matrix[i].resize(column);
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      WORKSPACE_matrix[i][j] = ui->Workspace->item(i, j)->text().toDouble();
    }
  }
  QDataStream out(&F);
  out.setVersion(QDataStream::Qt_5_4);
  WORKSPACE work(WORKSPACE_matrix);
  out << work;
  F.flush();
  F.close();
}
