#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0) : QWidget(parent){
        setLayout(new QVBoxLayout());
        QPushButton *btn =new QPushButton("close", this);
        layout()->addWidget(btn);
        connect(btn, &QPushButton::clicked, this,&Widget::close);
    }

    void close(){
        isCloseByFunction = true;
        QWidget::close();
    }

protected:
    void closeEvent(QCloseEvent *event){

        if(isCloseByFunction){
            qDebug()<<"call close() function";
        }
        else{
            qDebug()<<"press x button";
        }
        isCloseByFunction = false;
        QWidget::closeEvent(event);
    }

private:
    bool isCloseByFunction = false;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}

