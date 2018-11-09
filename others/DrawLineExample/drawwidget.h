#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void addWidgets(const QWidget *from, const QWidget *to);

protected:
    void paintEvent(QPaintEvent *);

private:
    struct WidgetsConnected {
        const QWidget* from;
        const QWidget* to;
    };

    QList<WidgetsConnected> list;

};

#endif // DRAWWIDGET_H
