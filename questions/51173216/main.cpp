#include "qcustomplot.h"

#include <QApplication>

class ChartWidget : public QCustomPlot {
public:
  ChartWidget(QWidget *parent = nullptr) : QCustomPlot(parent) {

    plotLayout()->clear();
    QCPAxisRect *leftAxisRect = new QCPAxisRect(this);
    QCPAxisRect *rightAxisRect = new QCPAxisRect(this);
    plotLayout()->addElement(0, 0, leftAxisRect);
    plotLayout()->addElement(0, 1, rightAxisRect);

    QVector<QCPGraphData> dataCos(100);

    for (int i = 0; i < dataCos.size(); ++i) {
      dataCos[i].key = i / (double)(dataCos.size() - 1) * 10 - 5.0;
      dataCos[i].value = qCos(dataCos[i].key);
    }

    QCPGraph *mainGraphCos = addGraph(leftAxisRect->axis(QCPAxis::atBottom),
                                      leftAxisRect->axis(QCPAxis::atLeft));
    mainGraphCos->data()->set(dataCos);
    mainGraphCos->valueAxis()->setRange(-1, 1);
    mainGraphCos->rescaleKeyAxis();
    mainGraphCos->setPen(QPen(QColor("blue"), 2));

    QVector<QCPGraphData> dataExp(100);

    for (int i = 0; i < dataExp.size(); ++i) {
      dataExp[i].key = i / (double)(dataExp.size() - 1) * 10 - 5.0;
      dataExp[i].value = qExp(dataExp[i].key) * qCos(dataExp[i].key);
    }

    QCPGraph *mainGraphExp = addGraph(rightAxisRect->axis(QCPAxis::atBottom),
                                      rightAxisRect->axis(QCPAxis::atLeft));
    mainGraphExp->data()->set(dataExp);
    mainGraphExp->keyAxis()->setRange(-5, 5);
    mainGraphExp->rescaleValueAxis();
    mainGraphExp->setPen(QPen(QColor("red"), 2));

    connect(this, &ChartWidget::mouseMove, this, &ChartWidget::showToolTip);
  }

private:
  void showToolTip(QMouseEvent *event) {
    for (QCPLayoutElement *element : plotLayout()->elements(true)) {
      QCPAxisRect *axisRect = static_cast<QCPAxisRect *>(element);
      if (axisRect) {
        if (axisRect->rect().contains(event->pos())) {
          double x =
              axisRect->axis(QCPAxis::atBottom)->pixelToCoord(event->x());
          double y = axisRect->axis(QCPAxis::atLeft)->pixelToCoord(event->y());
          setToolTip(tr("%1,%2").arg(x).arg(y));
          break;
        }
      }
    }
  }
};
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  ChartWidget w;
  w.resize(640, 480);
  w.show();

  return a.exec();
}
