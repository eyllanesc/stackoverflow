#ifndef DOUBLECLICKEDWIDGET_H
#define DOUBLECLICKEDWIDGET_H

#include <QWidget>
#include <QPainter>

class DoubleClickedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DoubleClickedWidget(QWidget *parent = nullptr):QWidget(parent){
        setFixedSize(20, 20);
    }

signals:
    void doubleClicked();
protected:
    void mouseDoubleClickEvent(QMouseEvent *){
        emit doubleClicked();
    }
    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        painter.fillRect(rect(), Qt::green);
    }
};

#endif // DOUBLECLICKEDWIDGET_H
