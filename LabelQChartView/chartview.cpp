#include "chartview.h"

ChartView::ChartView(QWidget *parent):QChartView(parent)
{
}

ChartView::ChartView(QChart *chart, QWidget *parent):QChartView(chart, parent)
{
}

void ChartView::showEvent(QShowEvent *event)
{
    QLineSeries* lineSerie;
    if(chart()){
        for(const auto& serie : chart()->series()){
            switch (serie->type()) {
            case QAbstractSeries::SeriesTypeLine:
                lineSerie = qobject_cast<QLineSeries*>(serie);
                for(int i=0; i < lineSerie->count(); i++){
                    auto item = new QGraphicsTextItem(QString::number(lineSerie->at(i).y()));
                    QPointF p = chart()->mapToPosition(lineSerie->at(i), lineSerie)- item->boundingRect().center();
                    item->setPos(p + QPointF(item->boundingRect().width(), 0)) ;
                    scene()->addItem(item);
                }
                break;
            default:
                break;
            }
        }
    }
    QChartView::showEvent(event);
}
