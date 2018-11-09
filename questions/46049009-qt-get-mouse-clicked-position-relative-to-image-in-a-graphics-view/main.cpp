#include <QApplication>
#include <QDialog>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QGraphicsLineItem>

#include <QDebug>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
    QGraphicsLineItem *item;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event){

        item = new QGraphicsLineItem;
        addItem(item);
        const QPointF p = event->scenePos();

        item->setPos(p);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        const QPointF p  =item->mapFromScene(event->scenePos());
        QLineF l = item->line();
        l.setP2(p);
        item->setLine(l);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
        const QPointF p  =item->mapFromScene(event->scenePos());
        QLineF l = item->line();
        l.setP2(p);
        item->setLine(l);
    }

};

class Dialog : public QDialog
{
    Q_OBJECT
    QGraphicsView *view;
    CustomScene *scene;
    QPushButton *btn;
public:
    Dialog(QWidget *parent=Q_NULLPTR):QDialog(parent){
        btn = new QPushButton("Load Image", this);
        view = new QGraphicsView(this);

        connect(btn, &QPushButton::clicked, this, &Dialog::LoadImage);

        scene = new CustomScene;
        view->setScene(scene);
        setLayout(new QVBoxLayout);
        layout()->addWidget(btn);
        layout()->addWidget(view);
    }

private slots:
    void LoadImage(){
        const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                              QDir::homePath(),
                                                              tr("Image Files (*.png *.jpg *.bmp)"));

        const QPixmap px(fileName);
        addImage(px);
    }

private:
    void addImage(const QPixmap &pixmap){
        scene->addPixmap(pixmap);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
