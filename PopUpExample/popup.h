#ifndef POPUP_H
#define POPUP_H

#include <QLabel>
#include <QWidget>

class PopUp : public QWidget
{
    Q_OBJECT
public:
    explicit PopUp(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
    QLabel *label;
};

#endif // POPUP_H
