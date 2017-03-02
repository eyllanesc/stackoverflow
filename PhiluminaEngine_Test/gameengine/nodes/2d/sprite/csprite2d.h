#ifndef CSPRITE2D_H
#define CSPRITE2D_H

#include <QString>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>


/**
 * @brief
 *
 */
class CSprite2D: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint pos READ getPos WRITE setPos)
    Q_PROPERTY(QString name READ getName WRITE setName)

public:
    /**
     * @brief
     *
     * @param parent
     */
    CSprite2D(QObject *parent=0);
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
    QString getName() const;
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
    QPoint getPos() const;
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

private:
    QString mName; /**< TODO: describe */
    QPoint mPos; /**< TODO: describe */

signals:
    /**
     * @brief
     *
     */
    void onChanged();

};

#endif // CSPRITE2D_H
