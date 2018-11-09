#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCamera>
#include <QHBoxLayout>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *m_QPushButton_calibration;
    QCamera *m_QCamera_required_camera;
    QHBoxLayout* layout;

public slots:
    void handleButton();

};

#endif // MAINWINDOW_H
