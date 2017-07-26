#include "focuslabel.h"

FocusLabel::FocusLabel(QWidget *parent, const QString &str) : QLabel(str, parent)
{
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setFontSize(12.0);
    setGeometry(0, 16, width(), height());
}

void FocusLabel::zoom(bool out)
{
    if (!m_zoomEnabled) { return; }

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    QPropertyAnimation *anmFont = new QPropertyAnimation(this, "fontSize", this),
            *anmPos = new QPropertyAnimation(this, "pos", this);

    anmFont->setEndValue(out ? 8.0 : 12.0);
    anmFont->setDuration(100);

    anmPos->setEndValue(QPoint(0, out ? 0 : 16));
    anmPos->setDuration(100);

    group->addAnimation(anmFont);
    group->addAnimation(anmPos);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void FocusLabel::enableZoom(bool value)
{
    m_zoomEnabled = value;
}

double FocusLabel::fontSize() const
{
    return m_fontSize;
}

void FocusLabel::setFontSize(double value)
{
    QFont f = font();

    f.setPointSizeF(value);
    setFont(f);
    adjustSize();

    m_fontSize = value;
}
