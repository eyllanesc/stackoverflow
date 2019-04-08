#include "mainwindow.h"
#include "chart.h"
#include "generatoraleator.h"
#include "tickdata.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QStringBuilder>
#include <QtCharts>
#include <QtGlobal>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), qcvChart(new QChartView),
      chart(new Chart) {
  ui->setupUi(this);
  this->index = 0;
  this->bCursorState = false;
  this->scaledZoom = 0;
  this->positionZoom = 0.2;
  GeneratorAleator::init();
  this->td1 = new TickData();

  this->chart->setPause(true);

  // Connexion
  //    QObject::connect(qobject_cast<QGraphicsView*>(this->qcvChart),
  //                     &QGraphicsView::rubberBandChanged,
  //                     this,
  //                     &MainWindow::rubberZoomAdapt);

  //    QObject::connect(this,
  //                     &MainWindow::rubberBandChanged,
  //                     this,
  //                     &MainWindow::rubberZoomAdapt);

  //    QObject::connect(this,
  //                     SIGNAL(this->rubberBandChanged(QPointF fp, QPoint tp)),
  //                     this,
  //                     SLOT(this->rubberZoomAdapt(QPointF fp, QPointF tp)));

  QObject::connect(ui->bSignalTest, &QPushButton::clicked, this,
                   &MainWindow::signalTest);

  // Controle
  this->qcvChart->setChart(this->chart);
  this->qcvChart->setContentsMargins(0, 0, 0, 0);
  this->qcvChart->setRubberBand(QChartView::NoRubberBand);
  ui->glChart->addWidget(this->qcvChart, 0, 0, Qt::AlignLeft | Qt::AlignBottom);
  ui->glChart->setSpacing(0);
  ui->glChart->setMargin(0);
  ui->glChart->setContentsMargins(0, 0, 0, 0);

  ui->dVitesse->setRange(10, 1000);
  ui->sZoom->setRange(0, 99);
  ui->sPosition->setRange(0, 100);
  ui->sPosition->setInvertedControls(true);
  ui->sPosition->setInvertedAppearance(true);

  this->td1->set_callBack_newData(
      std::bind(&MainWindow::callBack_newData, this));

  // Apparence
  this->qcvChart->setRenderHint(QPainter::Antialiasing);
  this->qcvChart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->qcvChart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  ui->sZoom->setSliderPosition(ui->sZoom->minimum());
  ui->lZoomValue->setText(QString::number(this->scaledZoom));
  ui->sPosition->setSliderPosition(int(ui->sPosition->maximum() * 0.2));
  ui->lPositionValue->setText(QString::number(this->positionZoom));
  ui->lCursorState->setPalette(QPalette(QPalette::Background, Qt::red));
  ui->lCursorState->setAutoFillBackground(true);
  ;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_bStart_clicked() {
  this->td1->startData();
  this->chart->setPause(false);
}

void MainWindow::on_bStop_clicked() {
  this->td1->stopData();
  this->chart->setPause(true);
}

void MainWindow::on_dVitesse_valueChanged(int value) {
  this->td1->setSpeed(value);
}

void MainWindow::on_sZoom_valueChanged(int value) {
  this->scaledZoom = (float)value / 100.0;
  this->chart->setZoom(this->scaledZoom);
  ui->lZoomValue->setText(QString::number(this->scaledZoom));
}

void MainWindow::on_sPosition_valueChanged(int value) {
  this->positionZoom = (float)value / 100.0;
  this->chart->setPosition(this->positionZoom);
  ui->lPositionValue->setText(QString::number(this->positionZoom));
}

void MainWindow::on_bResetZoom_clicked() {
  this->chart->zoomReset();
  ui->sZoom->setSliderPosition(ui->sZoom->minimum());
  ui->sPosition->setSliderPosition(int(ui->sPosition->maximum() * 0.2));
}

void MainWindow::on_bCursor_clicked() {
  if (this->bCursorState == false) {
    this->td1->stopData();
    this->chart->setPause(true);
    this->bCursorState = true;
    ui->bCursor->setText("Cursor Disable");
    ui->lCursorState->setPalette(QPalette(QPalette::Background, Qt::green));
    this->qcvChart->setRubberBand(QChartView::HorizontalRubberBand);

    qRubberBand = qcvChart->findChild<QRubberBand *>();
    qRubberBand->installEventFilter(this);
  } else {
    this->td1->startData();
    this->chart->setPause(false);
    this->bCursorState = false;
    ui->bCursor->setText("Cursor Enabled");
    ui->lCursorState->setPalette(QPalette(QPalette::Background, Qt::red));
    this->qcvChart->setRubberBand(QChartView::NoRubberBand);
  }
}

void MainWindow::rubberZoomAdapt(QPointF fp, QPointF tp) {
  static int i = 0;
  qDebug() << "(rubberZoomAdapt) RubberBand Event: " << QString::number(i++);
  qDebug() << "(rubberZoomAdapt) RubberBand Event: fp: " << fp
           << "; tp: " << tp;
  this->chart->zoomInRubberBand();
}

void MainWindow::signalTest(bool b) {
  static int i = 0;
  qDebug() << "(signalTest) pushbutton clicked: " << QString::number(i++);
}

void MainWindow::callBack_newData() {
  float value = GeneratorAleator::getNumber();
  this->chart->addValue(value);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  this->qcvChart->resize(ui->glChart->cellRect(0, 0).size());
  this->chart->resize(this->qcvChart->size());
  this->chart->setZoom(ui->sZoom->sliderPosition() / 100);
}

void MainWindow::showEvent(QShowEvent *event) {
  QMainWindow::showEvent(event);
  this->qcvChart->resize(ui->glChart->cellRect(0, 0).size());
  this->chart->resize(this->qcvChart->size());
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  static int i = 0;
  if ((watched == this->qRubberBand)) // && (event->type() == QEvent::Resize))
  {
    qDebug() << "(eventFilter) EventFilter: RubberBand: "
             << QString::number(i++);
    //        QPointF fp =
    //        this->chart->mapToValue(this->qRubberBand->geometry().topLeft());
    //        QPointF tp =
    //        this->chart->mapToValue(this->qRubberBand->geometry().bottomRight());
    //        emit this->rubberBandChanged(fp, tp);
  }

  return QMainWindow::eventFilter(watched, event);
}
