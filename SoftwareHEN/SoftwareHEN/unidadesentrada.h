#ifndef UNIDADESENTRADA_H
#define UNIDADESENTRADA_H
#include <QDialog>
#include "ventanaprincipal.h"
#include "unidadesentrada.h"
#include "tabladatos.h"

namespace Ui {
class UnidadesEntrada;
}

class UnidadesEntrada : public QDialog
{
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
