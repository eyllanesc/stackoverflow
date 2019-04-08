#ifndef CASCADECOLORHIGHLIGHTWIDGETITEM_H
#define CASCADECOLORHIGHLIGHTWIDGETITEM_H

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

class CascadeColorHighlightWidgetItem : public QWidget {
  Q_OBJECT
public:
  CascadeColorHighlightWidgetItem(int jobID, QColor selectedColor,
                                  QWidget *parent = 0);

  int getJobID();
  QString getSelectedColor();
  QString getColorText();

private:
  QString m_titleName;
  QRectF m_textRect;
  QVBoxLayout *m_mainLyt;

  QLineEdit *m_pTitleEditor;
  QLabel *m_ColorName;
  QColor m_SelectedColor;
};
#endif // CASCADECOLORHIGHLIGHTWIDGETITEM_H
