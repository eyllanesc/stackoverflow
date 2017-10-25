#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFuture>
#include <QFutureWatcher>
#include <QMainWindow>
#include <QMdiArea>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMdiArea *mdi;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayImage(const QImage &image, QString title);

private slots:
    void on_actionOpen_triggered();

    void on_actionOil_Paint_triggered();
    void onFinished();

private:
    Ui::MainWindow *ui;
    QFuture<QImage> future;
    QFutureWatcher<QImage> watcher;
};

#endif // MAINWINDOW_H
