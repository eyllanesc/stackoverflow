#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QDialog>
#include <QColor>
//#include "mainwindow.h"

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QDialog
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = 0);
    ~ColorPicker();

    QPalette palete;

    QColor color() const;

private slots:
    void onColorChanged();
    void onCMYKChanged();

private:
    Ui::ColorPicker *ui;
    double min(double a,double b,double c);

    QColor mColor;
    double k,c,m,y;
    int r,g,b;

signals:
    void colorChanged(QColor arg);
};

#endif // COLORPICKER_H
