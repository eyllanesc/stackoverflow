#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->customPlot->addGraph();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QSqlTableModel *model = new QSqlTableModel;
  model->setTable("empdata2");
  model->select();
  ui->tableView->setModel(model);

  ui->customPlot->xAxis->setLabel("Time");
  ui->customPlot->yAxis->setLabel("Temp");
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat("hh:mm");
  ui->customPlot->xAxis->setTicker(dateTicker);

  QVector<QCPGraphData> timeData(model->rowCount());

  for (int i = 0; i < model->rowCount(); ++i) {
    timeData[i].key =
        QDateTime(QDate::currentDate(),
                  model->index(i, model->fieldIndex("time")).data().toTime())
            .toTime_t();
    timeData[i].value =
        model->index(i, model->fieldIndex("temp")).data().toDouble();
  }

  double Tmin =
      (*std::min_element(timeData.begin(), timeData.end(),
                         [](const QCPGraphData &x, const QCPGraphData &y) {
                           return x.key < y.key;
                         }))
          .key;
  double Tmax =
      (*std::max_element(timeData.begin(), timeData.end(),
                         [](const QCPGraphData &x, const QCPGraphData &y) {
                           return x.key < y.key;
                         }))
          .key;

  double Ymin =
      (*std::min_element(timeData.begin(), timeData.end(),
                         [](const QCPGraphData &x, const QCPGraphData &y) {
                           return x.value < y.value;
                         }))
          .value;

  double Ymax =
      (*std::max_element(timeData.begin(), timeData.end(),
                         [](const QCPGraphData &x, const QCPGraphData &y) {
                           return x.value < y.value;
                         }))
          .value;

  ui->customPlot->xAxis->setRange(Tmin, Tmax);
  ui->customPlot->yAxis->setRange(Ymin, Ymax);
  ui->customPlot->graph(0)->data()->set(timeData);
  ui->customPlot->replot();
  ui->customPlot->setSizePolicy(ui->tableView->sizePolicy());
}
