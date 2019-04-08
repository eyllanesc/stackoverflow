#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDate>
#include <QEvent>
#include <QLineEdit>
#include <QQmlComponent>
#include <QQmlEngine>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit->installEventFilter(this);
  engine = new QQmlEngine(this);
  component = new QQmlComponent(
      engine, QUrl(QStringLiteral("qrc:/popupCalendar.qml")), this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (watched == ui->lineEdit) {
    if (event->type() == QEvent::MouseButtonPress) {
      showCalendar();
    }
  }
  return QMainWindow::eventFilter(watched, event);
}

void MainWindow::showCalendar() {
  if (dialog == Q_NULLPTR) {
    dialog = component->create();
    int index = dialog->metaObject()->indexOfProperty("selectedDate");
    const QMetaProperty property = dialog->metaObject()->property(index);
    if (property.hasNotifySignal()) {
      const QMetaMethod s = property.notifySignal();
      QString sig = QString("2%1").arg(QString(s.methodSignature()));
      connect(dialog, sig.toStdString().c_str(), this, SLOT(onSelectedDate()));
    }
  }
  QMetaObject::invokeMethod(dialog, "show",
                            Q_ARG(QVariant, QVariant(QDate::currentDate())));
}

void MainWindow::onSelectedDate() {
  ui->lineEdit->setText(dialog->property("selectedDate").toDate().toString());
  ui->lineEdit->adjustSize();
}
