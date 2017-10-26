#ifndef POSITIONWIDGET_H
#define POSITIONWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QResizeEvent>
#include <QWidget>

class PositionWidget : public QWidget
{
    Q_OBJECT

public:
    PositionWidget(QWidget *parent = 0):QWidget(parent){
        label = new QLabel("LABEL", this);
        lineEdit = new QLineEdit(this);
        setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    }
    ~PositionWidget(){

    }
protected:
    void resizeEvent(QResizeEvent *event){
        updatePosition(label, 0.5, 0.5); //50% , 50%
        updatePosition(lineEdit, 0.3, 0.7); //30% , 70%
        QWidget::resizeEvent(event);
    }
private:
    QLabel *label;
    QLineEdit *lineEdit;

    void updatePosition(QWidget *widget, float xscale, float yscale){
        int w = size().width();
        int h = size().height();
        widget->move( QPoint(w*xscale, h*yscale) - widget->rect().center());
    }
};

#endif // POSITIONWIDGET_H
