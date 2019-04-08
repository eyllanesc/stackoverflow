#ifndef UNIDADESENTRADA_H
#define UNIDADESENTRADA_H
#include "tabladatos.h"
#include "unidadesentrada.h"
#include "ventanaprincipal.h"
#include <QDialog>

namespace Ui {
class UnidadesEntrada;
}

class UnidadesEntrada : public QDialog {
  Q_OBJECT

public:
  explicit UnidadesEntrada(QWidget *parent = 0);
  ~UnidadesEntrada();

private slots:

private:
  Ui::UnidadesEntrada *ui;
  VentanaPrincipal *ventananueva;
};

#endif // UNIDADESENTRADA_H
