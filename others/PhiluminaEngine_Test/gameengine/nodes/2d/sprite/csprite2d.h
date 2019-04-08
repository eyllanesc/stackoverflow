#ifndef CSPRITE2D_H
#define CSPRITE2D_H

#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QString>

/**
 * @brief
 *
 */
class CSprite2D : public QObject {
  Q_OBJECT

  Q_PROPERTY(QPoint pos READ pos WRITE setPos)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QColor color READ color WRITE setColor)

public:
  /**
   * @brief
   *
   * @param parent
   */
  CSprite2D(QObject *parent = 0);
  /**
   * @brief
   *
   */
  ~CSprite2D();

  /**
   * @brief
   *
   * @return QString
   */
  QString name() const;
  /**
   * @brief
   *
   * @param name
   */
  void setName(const QString &name);

  /**
   * @brief
   *
   * @return QPoint
   */
  QPoint pos() const;
  /**
   * @brief
   *
   * @param pos
   */
  void setPos(const QPoint &pos);

  /**
   * @brief
   *
   * @param painter
   * @param event
   */
  void paint(QPainter *painter, QPaintEvent *event);

  QColor color() const;
  /**
   * @brief
   *
   * @param color
   */
  void setColor(const QColor &color);

private:
  QString mName; /**< TODO: describe */
  QPoint mPos;   /**< TODO: describe */
  QColor mColor;

signals:
  /**
   * @brief
   *
   */
  void onChanged();
};

#endif // CSPRITE2D_H
