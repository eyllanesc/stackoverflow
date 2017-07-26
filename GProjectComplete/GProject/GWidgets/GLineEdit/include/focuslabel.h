#ifndef FOCUSLABEL_H
#define FOCUSLABEL_H

#include <QObject>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

class FocusLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(double fontSize READ fontSize WRITE setFontSize)
public:
    FocusLabel(QWidget *parent, const QString &str);

public slots:
    void zoom(bool out);
    void enableZoom(bool value);

private:
    double fontSize() const;
    void setFontSize(double value);

    int m_fontSize;
    bool m_zoomEnabled = true;
};

#endif // FOCUSLABEL_H
