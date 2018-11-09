#ifndef DUVALORACTION_H
#define DUVALORACTION_H
#define WORKSPACE_FILENAME "./¨Workspace.bin"
#define TYPEOPERATION_FILENAME "./Typeoperation.bin"
#define TABPLOT_FILENAME "./Tabplot.bin"
#define GRAFOPERACIONES_FILENAME "./plots.bin"
#include <QDataStream>
#include <QVector>

class Duvaloraction
{
public:
    Duvaloraction(int valact = -1);
    void setvalact(int valact);
    int getvalact() const;

    friend QDataStream &operator<<(QDataStream &out,const Duvaloraction &valoraction);
    friend QDataStream &operator>>(QDataStream &in, Duvaloraction &valoraction);

private:
    int Mvalact;
};

class WORKSPACE
{
public:
    WORKSPACE(QVector<QVector<double>> Matriz);
    friend QDataStream &operator<<(QDataStream &out, const WORKSPACE &MATRIZ);
    friend QDataStream &operator>>(QDataStream &in, WORKSPACE &MATRIZ);
private:
    QVector<QVector<double>> MMatriz;

};

class Valordeoperacion
{
public:
    Valordeoperacion(int valor = -1);
    void setvalor(int valor);
    int getvalor() const;
    friend QDataStream &operator<<(QDataStream &out, const Valordeoperacion &valor);
    friend QDataStream &operator>>(QDataStream &in, Valordeoperacion &valor);
private:
    int Mvalor;
};

class Tabplot
{
public:
    Tabplot(int tabvalue = -1);
    void settabvalue(int tabvalue);
    int gettabvalue();
    friend QDataStream &operator<<(QDataStream &out, const Tabplot &tabvalue);
    friend QDataStream &operator>>(QDataStream &in, Tabplot &tabvalue);

private:
    int Mtabvalue;
};

class Operaciones
{
public:
    Operaciones(int tabval,int method,int analisis,int dtmin,int maximo,int minimo,int k,QVector<QVector<double>> Matriz);
    void operaciones(int tipo,int method,int analisis,int dtmin,int maximo,int minimo,int k,QVector<QVector<double>> Matriz);
private:
    int Mtabval,Mmethod,Manalisis,Mdtmin,Mmaximo,Mminimo,Mk,Mtipo;
    QVector<QVector<double>> MMatriz;
};

QDataStream &operator<<(QDataStream &out, const Tabplot &tabvalue);
QDataStream &operator>>(QDataStream &in, Tabplot &tabvalue);
QDataStream &operator<<(QDataStream &out, const WORKSPACE &MATRIZ);
QDataStream &operator>>(QDataStream &in, WORKSPACE &MATRIZ);
QDataStream &operator<<(QDataStream &out, const Duvaloraction &valor); //salida
QDataStream &operator>>(QDataStream &in, Duvaloraction &valoraction); //entrada

#endif // DUVALORACTION_H
