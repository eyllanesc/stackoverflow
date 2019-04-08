#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QQuickItem>
class QTextLayout;

class TextItem : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
public:
  TextItem(QQuickItem *parent = nullptr);
  ~TextItem();
  QString text() const;
  void setText(const QString &text);
  QFont font() const;
  void setFont(const QFont &font);
signals:
  void textChanged(const QString &);
  void fontChanged();

protected:
  QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
  QString m_text;
  QFont m_font;
  QTextLayout *m_layout;
};

#endif // TEXTITEM_H
