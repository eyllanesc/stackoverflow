#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWizardPage>

class CustomPage : public QWizardPage
{
    Q_OBJECT
    Q_ENUMS(Position)
public:
    enum Position{ topLeft, topRight, bottomLeft, bottomRight };
    CustomPage(QWidget * parent = 0);


    QRect rect() const;
    void setRect(const QRect &rect);

    int radius() const;
    void setRadius(int radius);

private:
    QRect mRect;
    int mRadius;
    Position mPosition;

signals:
    void onClicked(Position pos);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // CUSTOMPAGE_H
