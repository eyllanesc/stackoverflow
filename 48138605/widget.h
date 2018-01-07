#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QVBoxLayout;
class QComboBox;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QList<QWidget *> widget;
    QList<QVBoxLayout *> layout;
    QList<QComboBox *> box;
};

#endif // WIDGET_H
