#include "textitem.h"
#include <QFontMetrics>
#include <private/qquicktextnode_p.h>

TextItem::TextItem(QQuickItem *parent)
    : QQuickItem(parent), m_layout(new QTextLayout) {
  setFlag(ItemHasContents, true);
}

TextItem::~TextItem() { delete m_layout; }

QString TextItem::text() const { return m_text; }

void TextItem::setText(const QString &text) {
  if (m_text == text)
    return;
  m_text = text;
  emit textChanged(m_text);
  update();
}

QFont TextItem::font() const { return m_font; }

void TextItem::setFont(const QFont &font) {
  if (m_font == font)
    return;
  m_font = font;
  emit fontChanged();
  update();
}

QSGNode *TextItem::updatePaintNode(QSGNode *node,
                                   QQuickItem::UpdatePaintNodeData *data) {
  Q_UNUSED(data)
  QFontMetrics fontMetrics(font());
  int height = 0;
  int lineWidth = 40;
  int leading = fontMetrics.leading();
  m_layout->setText(m_text);
  m_layout->beginLayout();
  int counter = 1;
  while (1) {
    QTextLine line = m_layout->createLine();
    if (!line.isValid())
      break;
    line.setLineWidth(counter * lineWidth);
    height += leading;
    line.setPosition(QPointF(0, height));
    height += line.height();
    counter++;
  }
  m_layout->endLayout();

  QQuickTextNode *n = static_cast<QQuickTextNode *>(node);
  if (!n)
    n = new QQuickTextNode(this);
  n->removeAllChildNodes();
  n->addTextLayout(QPointF(5, 5), m_layout);
  return n;
}
