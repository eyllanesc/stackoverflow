#ifndef TABLADATOS_H
#define TABLADATOS_H

#include "duvaloraction.h"
#include "tabladatos.h"
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
#include <QWidget>
#include <QtAlgorithms>
#include <QtCore>
#include <QtGui>

namespace Ui {
class TablaDatos;
}

class TablaDatos : public QWidget {
  Q_OBJECT

public:
  explicit TablaDatos(QWidget *parent = 0);
  ~TablaDatos();

private slots:

  void on_Addcorrientes_clicked();
  void on_SIradioButton_clicked();
  void on_SISradioButton_clicked();
  void on_AddnewpushButton_clicked();
  void on_UploadExistinpushButton_clicked();
  void on_SavepushButton_clicked();
  void on_SavepushButton_2_clicked();
  void on_DeleteSelpushButton_clicked();
  void on_DeleteFirstpushButton_clicked();
  void on_DeleteLastpushButton_clicked();
  void on_DeleteAllpushButton_clicked();
  void on_Workspace_itemClicked(QTableWidgetItem *item);
  void on_treeView_clicked(const QModelIndex &index);
  void INICIO(int accion, int ANALISIS);
  // RECEPTORES DE LA SEÑAL
  void actionNewAC();
  void on_TypeAnalysis_currentIndexChanged(int index);

  void on_listView_doubleClicked(const QModelIndex &index);

  void on_Workspace_cellChanged(int row, int column);

private:
  QStringList titulos;
  QString sPath;
  int ValorTabla;
  Ui::TablaDatos *ui;
  int TamTabla;
  QString file_path;
  int BORRARFILA;
  QStringList Lista1, Lista2, Lista3;
  QFileSystemModel *dirmodel;
  QFileSystemModel *filemodel;
};

#endif // TABLADATOS_H
