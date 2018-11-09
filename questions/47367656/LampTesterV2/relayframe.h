#ifndef RELAYFRAME_H
#define RELAYFRAME_H

#include "relaycontroller.h"

#include <QFrame>

namespace Ui {
class RelayFrame;
}

class RelayFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RelayFrame(int pin, QWidget *parent = 0);
    ~RelayFrame();

private slots:
    void on_powerBrtn_toggled(bool checked);

    void on_onBtn_clicked();

    void on_offBtn_clicked();

private:
    Ui::RelayFrame *ui;
    RelayController *controller;
};

#endif // RELAYFRAME_H
