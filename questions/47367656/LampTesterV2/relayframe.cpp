#include "relayframe.h"
#include "ui_relayframe.h"
#include <QLCDNumber>

RelayFrame::RelayFrame(int pin, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RelayFrame)
{
    ui->setupUi(this);
    controller = new RelayController(pin);
    connect(controller, SIGNAL(changeCounter(int)), ui->cyclesLCD, SLOT(display(int)));
}

RelayFrame::~RelayFrame()
{
    delete ui;
}

void RelayFrame::on_powerBrtn_toggled(bool checked)
{
    if(checked)
        controller->start();
    else controller->stop();
}

void RelayFrame::on_onBtn_clicked()
{
    controller->relayHigh();
}

void RelayFrame::on_offBtn_clicked()
{
    controller->relayLow();
}
