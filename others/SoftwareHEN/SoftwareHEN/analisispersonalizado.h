#ifndef ANALISISPERSONALIZADO_H
#define ANALISISPERSONALIZADO_H

#include <QWidget>

namespace Ui {
class AnalisisPersonalizado;
}

class AnalisisPersonalizado : public QWidget {
  Q_OBJECT

public:
  explicit AnalisisPersonalizado(QWidget *parent = 0);
  ~AnalisisPersonalizado();

private slots:
  void on_StaticradioButton_clicked();

  void botones_uniformes();
  void botones_diversos();
  void on_IncrementradioButton_clicked();
  void Ucheckboxes_seleccionadas();
  void on_DStaticradioButton_clicked();

  void on_DIncrementradioButton_clicked();

  void on_UADTM_clicked();

  void on_UCDTM_clicked();

  void on_UAP_clicked();

  void on_UCP_clicked();

  void on_DAP_clicked();

  void on_DCP_clicked();

  void on_DADTM_clicked();

  void on_DCDTM_clicked();

private:
  Ui::AnalisisPersonalizado *ui;
};

#endif // ANALISISPERSONALIZADO_H
