#ifndef CONTENIDO_PLOTS_H
#define CONTENIDO_PLOTS_H

#include <QWidget>

namespace Ui {
class Contenido_PLOTS;
}

class Contenido_PLOTS : public QWidget
{
    Q_OBJECT

public:
    explicit Contenido_PLOTS(QWidget *parent = 0);
    ~Contenido_PLOTS();

private slots:

    void on_Uniforme_clicked(bool checked1);

    void on_Diverso_clicked(bool checked2);

    void on_StaticradioButton_clicked(bool checked3);

    void on_IncrementradioButton_clicked(bool checked4);

    void RADIOBUTTONS();

    void on_plot_push_clicked(bool checked);

private:
    Ui::Contenido_PLOTS *ui;
};

#endif // CONTENIDO_PLOTS_H
