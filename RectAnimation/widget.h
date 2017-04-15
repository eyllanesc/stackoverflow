#ifndef WIDGET_H
#define WIDGET_H

#include <QPaintEvent>
#include <QWidget>

#include "rectobject.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:

    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    RectObject *object;
};

#endif // WIDGET_H
