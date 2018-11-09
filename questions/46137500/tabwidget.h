#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabWidget>

class TabBar: public QTabBar
{
public:
    TabBar(const QHash<QString, QColor> &colors, QWidget *parent=0):QTabBar(parent){
        mColors = colors;
    }

protected:
    void paintEvent(QPaintEvent */*event*/){

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for(int i = 0;i < count();i++)
        {
            initStyleOption(&opt,i);
            if(mColors.contains(opt.text)){
                opt.palette.setColor(QPalette::Button, mColors[opt.text]);
            }

            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.drawControl(QStyle::CE_TabBarTabLabel,opt);
        }
    }


private:
    QHash<QString, QColor> mColors;
};

class TabWidget : public QTabWidget
{
public:
    TabWidget(QWidget *parent=0):QTabWidget(parent){
        QHash <QString, QColor> dict;

        dict["All"] = QColor("yellow");
        dict["purchase"] = QColor("#87ceeb");
        dict["POS Sales"] = QColor("#90EE90");
        dict["Cash Sales"] = QColor("pink");
        dict["invoice"] = QColor("#800080");

        setTabBar(new TabBar(dict));
    }
};

#endif // TABWIDGET_H
