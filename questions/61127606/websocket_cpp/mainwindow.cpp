#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->url_le->setText("ws://localhost:8080/name");
    onStateChanged(m_webSocket.state());
    connect(&m_webSocket, &QWebSocket::stateChanged, this, &MainWindow::onStateChanged);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::onTextMessageReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_btn_clicked()
{
    if(ui->open_btn->text() == "Open")
        m_webSocket.open(QUrl::fromUserInput(ui->url_le->text()));
    else
        m_webSocket.close();
}

void MainWindow::on_send_btn_clicked()
{
    if(m_webSocket.state() == QAbstractSocket::ConnectedState){
        QString message = ui->message_te->toPlainText();
        QJsonObject object {
            {"name", message}
        };
        QJsonDocument d(object);
        m_webSocket.sendTextMessage(d.toJson(QJsonDocument::Compact));
    }
}

void MainWindow::on_clear_btn_clicked()
{
    ui->log_te->clear();
}

void MainWindow::onTextMessageReceived(const QString &message)
{
    ui->log_te->appendPlainText(message);
}

void MainWindow::onStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        ui->status_lbl->setText("CLOSED");
        enableWidgets(false);
        ui->open_btn->setText("Open");
        break;
    case QAbstractSocket::ConnectingState:
        ui->status_lbl->setText("CONNECTING");
        break;
    case QAbstractSocket::ConnectedState:
        ui->status_lbl->setText("OPENED");
        enableWidgets(true);
        ui->open_btn->setText("Close");
        break;
    default:
        break;

    }

}

void MainWindow::enableWidgets(bool state)
{
    ui->send_btn->setEnabled(state);
    ui->clear_btn->setEnabled(state);
    ui->message_te->setEnabled(state);
}
