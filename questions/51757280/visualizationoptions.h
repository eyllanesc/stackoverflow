#ifndef VISUALIZATIONOPTIONS_H
#define VISUALIZATIONOPTIONS_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>

class VisualizationOptions : public QObject {
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<VisualizationOptions> childOptions READ options)
public:
  using QObject::QObject;
  virtual std::string getVisualizationName() const = 0;
  QQmlListProperty<VisualizationOptions> options() {
    return QQmlListProperty<VisualizationOptions>(
        this, this, &VisualizationOptions::appendOption,
        &VisualizationOptions::optionCount, &VisualizationOptions::option,
        &VisualizationOptions::clearOptions);
  }
  void appendOption(VisualizationOptions *p) { m_childsoptions.append(p); }
  int optionCount() const { return m_childsoptions.count(); }
  VisualizationOptions *option(int index) const {
    return m_childsoptions.at(index);
  }
  void clearOptions() { m_childsoptions.clear(); }

private:
  static void appendOption(QQmlListProperty<VisualizationOptions> *list,
                           VisualizationOptions *p) {
    reinterpret_cast<VisualizationOptions *>(list->data)->appendOption(p);
  }
  static void clearOptions(QQmlListProperty<VisualizationOptions> *list) {
    reinterpret_cast<VisualizationOptions *>(list->data)->clearOptions();
  }
  static VisualizationOptions *
  option(QQmlListProperty<VisualizationOptions> *list, int i) {
    return reinterpret_cast<VisualizationOptions *>(list->data)->option(i);
  }
  static int optionCount(QQmlListProperty<VisualizationOptions> *list) {
    return reinterpret_cast<VisualizationOptions *>(list->data)->optionCount();
  }
  QVector<VisualizationOptions *> m_childsoptions;
};

class LayoutOptions : public VisualizationOptions {
  Q_OBJECT
  Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
public:
  using VisualizationOptions::VisualizationOptions;
  std::string getVisualizationName() const { return "LayoutOptions"; }
  QString type() const { return mType; }
  void setType(const QString &type) {
    if (mType == type)
      return;
    mType = type;
    emit typeChanged();
  }
signals:
  void typeChanged();

private:
  QString mType;
};

class FooOptions : public VisualizationOptions {
  Q_OBJECT
public:
  using VisualizationOptions::VisualizationOptions;
  std::string getVisualizationName() const { return "FooOptions"; }
};

#endif // VISUALIZATIONOPTIONS_H
