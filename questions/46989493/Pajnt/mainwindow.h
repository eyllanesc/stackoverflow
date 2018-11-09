#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolwindow.h"

namespace Ui {
class MainWindow;
}

class QPainter;
class QImage;
extern int mSelection;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ToolWindow toolWindow;
    QColor mColor;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPainter *mPainter;
    QImage *mImage;
    QPixmap mPix;
    QPoint mBegin;
    QPoint mEnd;

    QRect mRect;
    QLine mLine;
    bool drawStarted;
    bool mPressed;
    int mSize;

};

#endif // MAINWINDOW_H
