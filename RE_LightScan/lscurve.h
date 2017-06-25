#ifndef LSCURVE_H
#define LSCURVE_H
#include <qwt_plot_curve.h>
class LSCurve{
public:
                    LSCurve();
                    ~LSCurve();
    bool            addPoint(double x, double y);
    bool            addPoint(double x[], double y[], int size);
    bool            reDraw(void);
    bool            removePoint(void);
    QwtPlotCurve *QwtCurve = new QwtPlotCurve();
private:
    double px[2048];
    double py[2048];
    int index = 0;
};
#endif // LSCURVE_H
