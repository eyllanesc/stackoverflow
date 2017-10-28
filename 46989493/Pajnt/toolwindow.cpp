#include "toolwindow.h"
#include "ui_toolwindow.h"
#include "colorpicker.h"
#include "mainwindow.h"

#include <QMouseEvent>

ToolWindow::ToolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolWindow)
{
    ui->setupUi(this);
}

ToolWindow::~ToolWindow()
{
    delete ui;
}

void ToolWindow::on_penTool_clicked()
{
    mSelection = 1;
}

void ToolWindow::on_rectTool_clicked()
{
    mSelection = 2;
}

void ToolWindow::on_selectTool_clicked()
{
    mSelection = 0;
}

void ToolWindow::on_circleTool_clicked()
{
    mSelection = 3;
}

void ToolWindow::on_lineTool_clicked()
{
    mSelection = 4;
}

void ToolWindow::on_colorButton_clicked()
{
    if(colorPicker.exec() == ColorPicker::Accepted){
        setColor(colorPicker.color());
    }
}

void ToolWindow::setColor(QColor color)
{
    ui->colorButton->setPalette(color);
}
