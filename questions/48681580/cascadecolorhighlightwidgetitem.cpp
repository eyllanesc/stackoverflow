#include "cascadecolorhighlightwidgetitem.h"

#include <QDebug>
#include <QLineEdit>
#include <QTextDocument>

CascadeColorHighlightWidgetItem::CascadeColorHighlightWidgetItem(
    int jobID, QColor selectedColor, QWidget *parent)
    : QWidget(parent), m_titleName("______"), m_SelectedColor(selectedColor) {

  Q_UNUSED(jobID)
  setFixedHeight(40);
  setContentsMargins(0, 0, 0, 0);
  setFocusPolicy(Qt::StrongFocus);

  m_pTitleEditor = new QLineEdit();

  m_ColorName = new QLabel("_________");
  m_ColorName->setTextInteractionFlags(Qt::TextSelectableByMouse |
                                       Qt::TextEditable);

  QFont font("Calibri");
  font.setPixelSize(14);
  m_ColorName->setFont(font);

  QPixmap pixmap;
  pixmap.fill(QColor("transparent"));
  QWidget *pixMap = new QWidget;
  pixMap->resize(100, 100);

  QString styl = QString("background-color: rgb(%1, %2, %3)")
                     .arg(QString::number(m_SelectedColor.red()),
                          QString::number(m_SelectedColor.green()),
                          QString::number(m_SelectedColor.blue()));
  pixMap->setStyleSheet(styl);

  // m_ColorToStringMap.insert(m_ColorName->text(),m_SelectedColor);

  QHBoxLayout *mnLyt = new QHBoxLayout(this);
  mnLyt->addWidget(pixMap);
  mnLyt->addWidget(m_ColorName);
  mnLyt->addSpacerItem(
      new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Minimum));

  int width = pixMap->width();
  int height = pixMap->height();

  int side = qMin(width, height);
  QRegion maskedRegion(width / 2 - side / 2, height / 2 - side / 2, 20, 20,
                       QRegion::Ellipse);
  pixMap->setMask(maskedRegion);
}

QString CascadeColorHighlightWidgetItem::getColorText() {
  QTextDocument *td = m_ColorName->findChild<QTextDocument *>();
  if (td) {
    qDebug() << td->toPlainText();
  }
  qDebug() << "!!!CascadeColorHighlightWidgetItem::getColorText"
           << m_ColorName->text(); // returns "_________"
  return m_ColorName->text();
}
