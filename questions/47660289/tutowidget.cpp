#include "tutowidget.h"

#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QEvent>
#include <QTimer>
#include <QPainter>

TutoWidget::TutoWidget(QWidget *parent):QWidget(0)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground, true);
    mParent = parent;
    mParent->installEventFilter(this);

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addItem(new QSpacerItem(20, 243, QSizePolicy::Minimum, QSizePolicy::Expanding));
    QHBoxLayout *hlay = new QHBoxLayout;
    vlay->addLayout(hlay);
    group = new QButtonGroup(this);
    const QStringList nameBtns{"Return", "Next"};
    for(int i=0; i < nameBtns.length(); i++){
        auto btn = new QPushButton(nameBtns[i]);
        btn->setFlat(true);
        group->addButton(btn, i);
        hlay->addWidget(btn);
    }
    connect(group, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this, static_cast<void (TutoWidget::*)(int)>(&TutoWidget::onClicked));
    hlay->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    group->button(0)->hide();
}

void TutoWidget::addPage(const QPoint &center, int radius, const QPoint &pText, const QString &text)
{
    pages << Pages{center, radius, pText, text};
    if(currentIndex == -1){
        currentIndex = 0;
        update();
    }
}

bool TutoWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched == mParent){

        switch (event->type()) {
        case QEvent::Show:
            QTimer::singleShot(10,  this, &QWidget::show);
            break;
        case QEvent::Close:
            close();
            break;
        case QEvent::Move:
            move(mParent->mapToGlobal(QPoint(0, 0)));
            break;
        case QEvent::Resize:
            resize(mParent->size());
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void TutoWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(100, 100, 100, 200));
    QPainterPath path;
    if(currentIndex != -1){
        QPoint center = pages[currentIndex].center;
        int radius = pages[currentIndex].radius;
        QString text = pages[currentIndex].text;
        QPoint pText = pages[currentIndex].pText;
        path.moveTo(center + radius/2*QPoint(1, 0));
        path.arcTo(QRect(center-radius/2*QPoint(1, 1),radius*QSize(1, 1)), 0, 360);
        path.addText(pText, font(), text);
    }
    path.addRect(rect());
    painter.drawPath(path);
}

void TutoWidget::onClicked(int id)
{
    if(id == 0){
        if(currentIndex > 0)
            currentIndex--;
    }
    else if(id == 1){
        if(currentIndex < pages.count()-1)
            currentIndex++;
    }
    update();
    group->button(0)->setVisible(currentIndex!=0);
    group->button(1)->setVisible(currentIndex!=(pages.count()-1));
}
