#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class LogWindow: public QWidget{
    Q_OBJECT
public:
    LogWindow(const QString &text, QWidget *parent=Q_NULLPTR):QWidget(parent){
        setLayout(new QVBoxLayout);
        btn = new QPushButton(text, this);
        layout()->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, &LogWindow::customSignal);
    }
signals:
    void customSignal();
private:
    QPushButton *btn;
};

class RegWindow : public QWidget{
    QLabel *label;
public:
    RegWindow(const QString &text, QWidget *parent=Q_NULLPTR):QWidget(parent){
        setLayout(new QVBoxLayout);
        label = new QLabel(text, this);
        layout()->addWidget(label);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogWindow *log= new LogWindow("LogWindow");
    RegWindow *reg;
    QObject::connect(log, &LogWindow::customSignal, [&reg, &log](){
        reg = new RegWindow("RegWindow");
        reg->show();
        log->deleteLater();
    });
    log->show();
    return a.exec();
}

#include "main.moc"
