#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPropertyAnimation>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    object = new RectObject;

    QPropertyAnimation *animation = new QPropertyAnimation(object, "rect");
    //animation->setEasingCurve(QEasingCurve::InBack);
    animation->setDuration(1000);
    animation->setStartValue(QRect(0, 0, 10, 10));
    animation->setEndValue(QRect(0, 0, 200, 200));
    animation->start();
    connect(animation, &QPropertyAnimation::valueChanged, [=](){
        update();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QRect ellipse(object->rect());
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse);
}
