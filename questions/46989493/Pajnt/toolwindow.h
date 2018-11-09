#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QDialog>
#include "colorpicker.h"
//#include "mainwindow.h"

namespace Ui {
class ToolWindow;
}

class ToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolWindow(QWidget *parent = 0);
    ~ToolWindow();
   void setColor(QColor color);


private slots:
    void on_penTool_clicked();
    void on_rectTool_clicked();
    void on_selectTool_clicked();
    void on_circleTool_clicked();
    void on_lineTool_clicked();
    void on_colorButton_clicked();

private:
    Ui::ToolWindow *ui;
    ColorPicker colorPicker;
    QColor nColor;

};

#endif // TOOLWINDOW_H
