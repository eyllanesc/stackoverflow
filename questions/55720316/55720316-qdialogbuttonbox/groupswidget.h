#ifndef GROUPSWIDGET_H
#define GROUPSWIDGET_H

#include <QWidget>

namespace Ui {
class GroupsWidget;
}

class GroupsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupsWidget(QWidget *parent = nullptr);
    ~GroupsWidget();

private:
    Ui::GroupsWidget *ui;
};

#endif // GROUPSWIDGET_H
