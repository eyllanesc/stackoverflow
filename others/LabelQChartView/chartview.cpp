#include "chartview.h"

#include <QDebug>
#include <QMutableListIterator>
#include <QResizeEvent>

ChartView::ChartView(QWidget *parent) : QChartView(parent) {}

ChartView::ChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent) {}

void ChartView::showEvent(QShowEvent *event) {
  drawLabels();
  QChartView::showEvent(event);
}

void ChartView::resizeEvent(QResizeEvent *event) {

  if (chart())
    if (chart()->scene()) {
      for (const auto &it : textItems)
        chart()->scene()->removeItem(it);
    }
  textItems.clear();
  drawLabels();
  QChartView::resizeEvent(event);
}

void ChartView::drawLabels() {
  QLineSeries *lineSerie;
  if (chart())
    if (chart()->scene())
      for (const auto &serie : chart()->series())
        switch (serie->type()) {
        case QAbstractSeries::SeriesTypeLine:
          lineSerie = qobject_cast<QLineSeries *>(serie);
          for (int i = 0; i < lineSerie->count(); i++) {
            auto item =
                new QGraphicsTextItem(QString::number(lineSerie->at(i).y()));
            QPointF p = chart()->mapToPosition(lineSerie->at(i), lineSerie) -
                        item->boundingRect().center();
            item->setPos(p);
            textItems.append(item);
            scene()->addItem(item);
          }
          break;
        default:
          break;
        }
}
