#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), qcvChart(new QChartView),
      chart(new QChart) {
  ui->setupUi(this);

  qcvChart->setChart(chart);
  qcvChart->setRubberBand(QChartView::HorizontalRubberBand);
  rubberBand = qcvChart->findChild<QRubberBand *>();
  rubberBand->installEventFilter(this);

  connect(this, &MainWindow::rubberBandChanged, this,
          &MainWindow::rubberZoomAdapt);

  setCentralWidget(qcvChart);

  QLineSeries *series = new QLineSeries;
  series->append(0, 6);
  series->append(2, 4);
  series->append(3, 8);
  series->append(7, 4);
  series->append(10, 5);
  *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6)
          << QPointF(18, 3) << QPointF(20, 2);
  chart->addSeries(series);
  chart->createDefaultAxes();
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (watched == rubberBand && event->type() == QEvent::Resize) {

    QPointF fp = chart->mapToValue(rubberBand->geometry().topLeft());
    QPointF tp = chart->mapToValue(rubberBand->geometry().bottomRight());
    emit rubberBandChanged(fp, tp);
  }
  return QMainWindow::eventFilter(watched, event);
}

void MainWindow::rubberZoomAdapt(QPointF fp, QPointF tp) {
  qDebug() << "(rubberZoomAdapt) RubberBand Event: " << fp << tp;
}
