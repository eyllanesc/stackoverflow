#ifndef CUSTOM_CLASS_H
#define CUSTOM_CLASS_H

#include <QObject>

class CustomClass : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)
public:
  CustomClass(QObject *parent = nullptr) : QObject(parent) {}

  CustomClass(QString name) { name_ = name; }

  CustomClass(const CustomClass &item) { name_ = item.name_; }

  QString name() const { return name_; }

  void setName(QString name) { name_ = name; }

private:
  QString name_;
};

Q_DECLARE_METATYPE(CustomClass)

#endif // CUSTOM_CLASS_H
