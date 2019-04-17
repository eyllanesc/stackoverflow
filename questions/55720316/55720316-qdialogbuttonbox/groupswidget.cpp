#include "groupswidget.h"
#include "ui_groupswidget.h"

GroupsWidget::GroupsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupsWidget)
{
    ui->setupUi(this);
}

GroupsWidget::~GroupsWidget()
{
    delete ui;
}
