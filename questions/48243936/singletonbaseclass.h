#ifndef SINGLETONBASECLASS_H
#define SINGLETONBASECLASS_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include <QDebug>

class SingletonBaseClass : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
  explicit SingletonBaseClass(QObject *parent = nullptr) : QObject(parent) {}
  QString text() const { return mText; }

  void setText(const QString &text) {
    if (mText == text)
      return;
    mText = text;
    emit textChanged();
  }

  Q_INVOKABLE void someMethodCalledFromQml() {
    QQmlEngine *ownerEngine = QQmlEngine::contextForObject(this)->engine();
    qDebug() << ownerEngine;
  }

  static SingletonBaseClass *instance(QQmlEngine *engine) {
    QQmlComponent component(engine, QUrl("qrc:/tmp.qml"));
    QObject *item = component.create();
    SingletonBaseClass *instance =
        qvariant_cast<SingletonBaseClass *>(item->property("obj"));
    return instance;
  }
signals:
  void textChanged();

private:
  QString mText;
};

#endif // SINGLETONBASECLASS_H
