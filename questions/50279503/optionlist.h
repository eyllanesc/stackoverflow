#ifndef OPTIONLIST_H
#define OPTIONLIST_H

#include <QListWidget>

class OptionList : public QListWidget {
public:
  OptionList(QWidget *parent = nullptr);

protected:
  void startDrag(Qt::DropActions supportedActions);
};

#endif // OPTIONLIST_H
