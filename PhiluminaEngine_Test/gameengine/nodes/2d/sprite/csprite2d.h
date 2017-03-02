#ifndef CSPRITE2D_H
#define CSPRITE2D_H

#include <QString>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>


class CSprite2D: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint pos READ getPos WRITE setPos)
    Q_PROPERTY(QString name READ getName WRITE setName)

public:
    CSprite2D(QObject *parent=0);
    ~CSprite2D();

    QString getName() const;
    void setName(const QString &name);

    QPoint getPos() const;
    void setPos(const QPoint &pos);

    void paint(QPainter *painter, QPaintEvent *event);

private:
    QString mName;
    QPoint mPos;

};

#endif // CSPRITE2D_H
