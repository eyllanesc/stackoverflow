#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QVideoWidget>

#include <QDebug>

class VideoWidgetButton: public QWidget{
    QPushButton *btn;
    QVideoWidget *vw;
    QMediaPlayer *player;
public:
    VideoWidgetButton(QWidget *parent=Q_NULLPTR):QWidget(parent){
        setLayout(new QVBoxLayout);
        layout()->setContentsMargins(0, 0, 0, 0);
        installEventFilter(this);

        vw = new QVideoWidget(this);
        btn = new QPushButton(this);
        btn->setIcon(QIcon(":/icons/tux.jpeg"));
        btn->resize(QSize(128, 128));
        btn->setIconSize(QSize(128, 128));

        connect(btn, &QPushButton::clicked, [](){
            qDebug()<<"clicked";
        });

        layout()->addWidget(vw);

        player = new QMediaPlayer(this);
        player->setVideoOutput(vw);

        QMediaPlaylist *playList = new QMediaPlaylist(this);
        playList->addMedia(QUrl("qrc:/video/SampleVideo_1280x720_1mb.mp4"));
        playList->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playList);
        player->play();

    }
protected:
    void resizeEvent(QResizeEvent *ev){
        btn->move(rect().bottomRight()-btn->rect().bottomRight());
        return QWidget::resizeEvent(ev);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoWidgetButton w;
    w.resize(640, 480);
    w.show();
    return a.exec();
}
