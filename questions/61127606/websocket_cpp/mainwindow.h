#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebSockets/QtWebSockets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_btn_clicked();
    void on_send_btn_clicked();
    void on_clear_btn_clicked();
    void onTextMessageReceived(const QString & message);
    void onStateChanged(QAbstractSocket::SocketState state);
private:
    void enableWidgets(bool state);
    Ui::MainWindow *ui;
    QWebSocket m_webSocket;
};
#endif // MAINWINDOW_H
