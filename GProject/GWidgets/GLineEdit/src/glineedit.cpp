#include "glineedit.h"

GLineEdit::GLineEdit(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_label = new FocusLabel(this, "");
    m_label->setStyleSheet("QLabel { color: rgb(0, 0, 0); }");
    m_lineEdit = new FocusLineEdit(this);
    m_lineEdit->setStyleSheet(QString("QLineEdit { font-size: 12pt; padding-bottom: 5px; border: none; background-color: transparent; border-bottom: 2px solid %1; color: %1;}").arg("rgb(0, 0, 0)"));

    layoutMain->addSpacerItem(new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layoutMain->addWidget(m_lineEdit);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);

    connect(m_lineEdit, &FocusLineEdit::focusChanged, m_label, &FocusLabel::zoom);
    connect(m_lineEdit, &FocusLineEdit::cleared, m_label, &FocusLabel::enableZoom);
}

QString GLineEdit::text() const
{
    return m_lineEdit->text();
}

void GLineEdit::setText(const QString &str)
{
    m_lineEdit->setText(str);
}

void GLineEdit::setTitle(const QString &str)
{
    m_label->setText(str);
}
