#ifndef TUTOWIDGET_H
#define TUTOWIDGET_H

#include <QWidget>
class QButtonGroup;

class TutoWidget : public QWidget
{
    Q_OBJECT
    struct Pages{
        QPoint center;
        int radius;
        QPoint  pText;
        QString text;
    };
public:
    TutoWidget(QWidget *parent);
    void addPage(const QPoint &center, int radius, const QPoint &pText, const QString & text);
    bool eventFilter(QObject *watched, QEvent *event);
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void onClicked(int id);
private:
    QWidget *mParent;
    QButtonGroup *group;
    QVector<Pages> pages;
    int currentIndex = -1;
};

#endif // TUTOWIDGET_H
