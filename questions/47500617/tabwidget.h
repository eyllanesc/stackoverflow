#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabWidget>

class TabBar: public QTabBar
{
protected:
    void paintEvent(QPaintEvent */*event*/){

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for(int i = 0;i < count();i++)
        {   
            initStyleOption(&opt,i);

            QPoint c = tabRect(i).center();
            painter.translate(c);
            painter.rotate(-180);
            painter.translate(-c);
            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.resetTransform();

            painter.drawControl(QStyle::CE_TabBarTabLabel,opt);
        }
    }
};

class TabWidget : public QTabWidget
{
public:
    TabWidget(QWidget *parent=0):QTabWidget(parent){
        setTabBar(new TabBar);
        setTabShape(QTabWidget::Triangular);
    }
};

#endif // TABWIDGET_H
