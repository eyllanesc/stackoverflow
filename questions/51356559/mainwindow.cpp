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
#include <QDebug>
void MainWindow::on_pushButton_clicked() {
  QSqlTableModel *model = new QSqlTableModel;
  model->setTable("empdata");
  model->select();
  ui->tableView->setModel(model);

  ui->customPlot->xAxis->setLabel("Time");
  ui->customPlot->yAxis->setLabel("Temp");
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat("dd/MM/yyyy hh:mm:ss");
  ui->customPlot->xAxis->setTicker(dateTicker);

  QVector<QCPGraphData> timeData(model->rowCount());

  for (int i = 0; i < model->rowCount(); ++i) {
    timeData[i].key = model->index(i, model->fieldIndex("time"))
                          .data()
                          .toDateTime()
                          .toTime_t();
    timeData[i].value =
        model->index(i, model->fieldIndex("temperature")).data().toDouble();
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
