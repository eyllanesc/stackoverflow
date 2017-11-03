#include <QApplication>
#include <QLabel>
#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabWidget>

class TabBar: public QTabBar{
    QVector<int> mUnSaved;
public:
    void setUnsaved(int index){
        if(index >= count() || index < 0)
            return;
        mUnSaved << index;
        update();
    }
    void setSaved(int index){
        if(!mUnSaved.contains(index))
            return;
        mUnSaved.remove(mUnSaved.indexOf(index));
        update();
    }
protected:
    void paintEvent(QPaintEvent */*event*/){

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for(int i = 0;i < count();i++)
        {
            initStyleOption(&opt,i);
            painter.save();
            if(mUnSaved.contains(i)){
                painter.setFont(QFont("Times", 10, QFont::Bold));
            }
            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.drawControl(QStyle::CE_TabBarTabLabel,opt);
            painter.restore();
        }
    }
};

class TabWidget : public QTabWidget
{
    TabBar *mTabBar;
public:
    TabWidget(QWidget *parent=0):QTabWidget(parent){
        mTabBar = new TabBar;
        setTabBar(mTabBar);
        for(int i=0; i < 5; i++){
            QString text = QString("Tab %1").arg(i);
            addTab(new QLabel(text, this), text);
        }
        mTabBar->setUnsaved(1);
        mTabBar->setUnsaved(3);
        mTabBar->setUnsaved(4);
        mTabBar->setSaved(3);
        mTabBar->setSaved(10);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    TabWidget w;
    w.show();
    return a.exec();
}
