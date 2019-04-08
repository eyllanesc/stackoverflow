#include "duvaloraction.h"

Duvaloraction::Duvaloraction(int valact) { Mvalact = valact; }

int Duvaloraction::getvalact() const // GETTER
{
  return Mvalact;
}

void Duvaloraction::setvalact(int valact) // SETTER
{
  Mvalact = valact;
}

QDataStream &operator<<(QDataStream &out, const Duvaloraction &valoraction) {
  return out << valoraction.Mvalact;
}

QDataStream &operator>>(QDataStream &in, Duvaloraction &valoraction) {
  return in >> valoraction.Mvalact;
}

WORKSPACE::WORKSPACE(QVector<QVector<double>> Matriz) { MMatriz = Matriz; }

QDataStream &operator<<(QDataStream &out, const WORKSPACE &MATRIZ) {
  return out << MATRIZ.MMatriz;
}

QDataStream &operator>>(QDataStream &in, WORKSPACE &MATRIZ) {
  return in >> MATRIZ.MMatriz;
}

QDataStream &operator<<(QDataStream &out, const Valordeoperacion &valorop) {
  return out << valorop.Mvalor;
}

QDataStream &operator>>(QDataStream &in, Valordeoperacion &valorop) {
  return in >> valorop.Mvalor;
}

Valordeoperacion::Valordeoperacion(int valor) { Mvalor = valor; }

void Valordeoperacion::setvalor(int valor) { Mvalor = valor; }

int Valordeoperacion::getvalor() const { return Mvalor; }

Tabplot::Tabplot(int tabvalue) { Mtabvalue = tabvalue; }

void Tabplot::settabvalue(int tabvalue) { Mtabvalue = tabvalue; }

int Tabplot::gettabvalue() { return Mtabvalue; }

QDataStream &operator<<(QDataStream &out, const Tabplot &tabvalue) {
  return out << tabvalue.Mtabvalue;
}

QDataStream &operator>>(QDataStream &in, Tabplot &tabvalue) {
  return in >> tabvalue.Mtabvalue;
}

Operaciones::Operaciones(int tabval, int method, int analisis, int dtmin,
                         int maximo, int minimo, int k,
                         QVector<QVector<double>> Matriz) {
  Mtabval = tabval;
  Mmethod = method;
  Manalisis = analisis;
  Mdtmin = dtmin;
  Mmaximo = maximo;
  Mminimo = minimo;
  Mk = k;
  MMatriz = Matriz;
}

void Operaciones::operaciones(int tipo, int method, int analisis, int dtmin,
                              int maximo, int minimo, int k,
                              QVector<QVector<double>> Matriz) {
  // aun si declarar nada
}
