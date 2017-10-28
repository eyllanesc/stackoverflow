#include "colorpicker.h"
#include "ui_colorpicker.h"
#include "toolwindow.h"
#include "mainwindow.h"

#include <QPalette>

ColorPicker::ColorPicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);
    connect(ui->redSlider,SIGNAL(valueChanged(int)),SLOT(onColorChanged()));
    connect(ui->greenSlider,SIGNAL(valueChanged(int)),SLOT(onColorChanged()));
    connect(ui->blueSlider,SIGNAL(valueChanged(int)),SLOT(onColorChanged()));
    connect(ui->blackSlider,SIGNAL(valueChanged(int)),SLOT(onCMYKChanged()));
    connect(ui->yellowSlider,SIGNAL(valueChanged(int)),SLOT(onCMYKChanged()));
    connect(ui->magentaSlider,SIGNAL(valueChanged(int)),SLOT(onCMYKChanged()));
    connect(ui->cyanSlider,SIGNAL(valueChanged(int)),SLOT(onCMYKChanged()));
    //connect(this,SIGNAL(colorChanged(QColor)),toolWindow,SLOT(setColor(QColor)));
    onColorChanged();

}

ColorPicker::~ColorPicker()
{
    delete ui;
}

double ColorPicker::min(double a,double b,double c)
{
    double tmp;
    if(a>b)
    {
        if(a>c)
            tmp = a;
        else
            tmp = c;
    }
    else
    {
        if(b>c)
            tmp = b;
        else
            tmp = c;
    }
    return tmp;
}

QColor ColorPicker::color() const
{
    return mColor;
}


void ColorPicker::onColorChanged()
{
    int q1,q2,q3;
    mColor.setRgb(ui->redSlider->value(),ui->greenSlider->value(),ui->blueSlider->value());
    q1=ui->redSlider->value();
    q2=ui->greenSlider->value();
    q3=ui->blueSlider->value();
    palete = ui->widget->palette();
    palete.setColor(QPalette::Window, mColor);
    ui->widget->setPalette(palete);
    emit colorChanged(mColor);
    k=min(q1,q2,q3);
    c=(1-ui->redSlider->value()-k)/(1-k);
    m=(1-ui->greenSlider->value()-k)/(1-k);
    y=(1-ui->blueSlider->value()-k)/(1-k);
    ui->blackSlider->setValue(k);
    ui->cyanSlider->setValue(c);
    ui->magentaSlider->setValue(m);
    ui->yellowSlider->setValue(y);

}
void ColorPicker::onCMYKChanged()
{
    mColor.setRgb(ui->redSlider->value(),ui->greenSlider->value(),ui->blueSlider->value());
    palete = ui->widget->palette();
    palete.setColor(QPalette::Window, mColor);
    ui->widget->setPalette(palete);
    emit colorChanged(mColor);
}
