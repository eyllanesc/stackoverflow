#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QDebug>
#include <QQuickItem>
class MyQuickItem : public QQuickItem {
  Q_OBJECT
public:
  MyQuickItem(QQuickItem *parent = Q_NULLPTR) : QQuickItem(parent) {}

protected:
  void componentComplete() {
    int index = metaObject()->indexOfProperty("nextColor");
    const QMetaProperty property = metaObject()->property(index);
    if (property.hasNotifySignal()) {
      const QMetaMethod s = property.notifySignal();
      QString sig = QString("2%1").arg(QString(s.methodSignature()));
      connect(this, sig.toStdString().c_str(), this,
              SLOT(onNextColorChanged()));
    }
  }
private slots:
  void onNextColorChanged() {
    int index = metaObject()->indexOfProperty("nextColor");
    const QMetaProperty property = metaObject()->property(index);
    qDebug() << "color" << property.read(this);
  }
};

#endif // MYQUICKITEM_H
