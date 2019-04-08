#ifndef VIZFACTORY_H
#define VIZFACTORY_H

#include "visualizationoptions.h"
#include <QQuickItem>

class VizFactory : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(VisualizationOptions *options READ options WRITE setOptions)
public:
  VizFactory(QQuickItem *parent = nullptr) : QQuickItem(parent) {}
  ~VizFactory() {}
  VisualizationOptions *options() { return m_visualizationOptions; }
  void setOptions(VisualizationOptions *options) {
    m_visualizationOptions = options;
  }

private:
  VisualizationOptions *m_visualizationOptions;
};

#endif // VIZFACTORY_H
