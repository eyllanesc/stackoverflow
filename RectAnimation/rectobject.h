#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include <QObject>
#include <QRect>

class RectObject : public QObject
{
    Q_OBJECT
public:
    explicit RectObject(QObject *parent = 0);
    Q_PROPERTY(QRect rect READ rect WRITE setRect)

    QRect rect() const;
    void setRect(const QRect &value);

public slots:

private:
    QRect mRect;
};

#endif // RECTOBJECT_H
