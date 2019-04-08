#include "speedometer.h"

#include <qwt_dial_needle.h>

#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

SpeedoMeter::SpeedoMeter(QWidget *parent) : QwtDial(parent), d_label("km/h") {
  setAcceptDrops(true);
  QwtDialSimpleNeedle *nd =
      new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow, Qt::white, Qt::red);
  setNeedle(nd);
  setValue(80);
}

void SpeedoMeter::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    event->acceptProposedAction();
}

void SpeedoMeter::dropEvent(QDropEvent *event) {
  const QMimeData *mimedata = event->mimeData();

  if (mimedata->hasFormat("application/x-qabstractitemmodeldatalist")) {
    QString text;
    // https://stackoverflow.com/questions/1723989/how-to-decode-application-x-qabstractitemmodeldatalist-in-qt-for-drag-and-drop
    QByteArray encoded =
        mimedata->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    while (!stream.atEnd()) {
      int row, col;
      QMap<int, QVariant> roleDataMap;
      stream >> row >> col >> roleDataMap;
      if (roleDataMap.contains(Qt::DisplayRole)) {
        text = roleDataMap[Qt::DisplayRole].toString();
        break;
      }
    }
    // your text
    d_label = text;
    update();
  }
}

void SpeedoMeter::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    event->accept();
}

void SpeedoMeter::paintEvent(QPaintEvent *event) {
  // https://stackoverflow.com/questions/43904204/qwt-dial-show-unit
  QwtDial::paintEvent(event);
  QPainter painter(this);
  painter.setPen(Qt::black);
  QFont font;
  font.setPointSize(11);
  painter.setFont(font);
  QString text = QString("%1 %2").arg(value()).arg(d_label);
  QPoint c = rect().center();
  QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, text);
  painter.drawText(
      QPointF(c.x() - Size.width() / 2, c.y() + 2.5 * Size.height()), text);
}
