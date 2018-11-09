#ifndef TRACKWINDOW_H
#define TRACKWINDOW_H

#include <QWidget>

namespace Ui {
class TrackWindow;
}

class TrackWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TrackWindow(QWidget *parent = 0);
    ~TrackWindow();

private:
    Ui::TrackWindow *ui;
};

#endif // TRACKWINDOW_H
