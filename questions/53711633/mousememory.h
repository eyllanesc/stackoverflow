#ifndef MOUSEMEMORY_H
#define MOUSEMEMORY_H

#include <QObject>

class MouseMemory : public QObject {
  Q_OBJECT
public:
  explicit MouseMemory(QObject *parent = nullptr);
  Q_INVOKABLE void clear();
};

#endif // MOUSEMEMORY_H
