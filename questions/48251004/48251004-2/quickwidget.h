#ifndef QUICKWIDGET_H
#define QUICKWIDGET_H

#include <QQuickWidget>

class QuickWidget : public QQuickWidget {
public:
  QuickWidget(QWidget *parent = Q_NULLPTR) : QQuickWidget(parent) {
    setSource(QUrl("qrc:/places_map.qml"));
    setResizeMode(QQuickWidget::SizeRootObjectToView);
  }
};

#endif // QUICKWIDGET_H
