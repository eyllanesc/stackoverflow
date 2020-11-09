#include "score.h"

#include <QTimer>
#include <QDebug>

Score::Score(QObject *parent) : QObject(parent)
{
    score = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Score::update);
}

void Score::start()
{
    timer->start(1000);
}

void Score::stop()
{
    timer->stop();
}

int Score::getScore()
{
    return score;
}

void Score::update()
{
    score += 10;
    qDebug() << score;
}
