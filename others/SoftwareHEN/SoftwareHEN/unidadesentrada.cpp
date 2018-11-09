#include "unidadesentrada.h"
#include "ui_unidadesentrada.h"
#include "ventanaprincipal.h"
#include "tabladatos.h"
#include <QPixmap>
#include <QMessageBox>

UnidadesEntrada::UnidadesEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnidadesEntrada)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/Resources/NuevaPresentacion.png");
    int w = ui->ImagenPrograma->width();
    int h = ui->ImagenPrograma->height();
    ui->ImagenPrograma->setPixmap(pix.scaled(w+150,h+100,Qt::KeepAspectRatio));
}

UnidadesEntrada::~UnidadesEntrada()
{
    delete ui;
}
