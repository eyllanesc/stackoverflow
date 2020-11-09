#ifndef SCORE_H
#define SCORE_H

#include <QObject>

class QTimer;

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(QObject *parent = nullptr);
    void start();
    void stop();
    int getScore();

private slots:
    void update();

private:
    int score;
    QTimer *timer;
};

#endif // SCORE_H
