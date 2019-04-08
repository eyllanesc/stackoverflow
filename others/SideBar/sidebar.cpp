#include "sidebar.h"

#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>

#define action_height 90

SideBar::SideBar(QWidget *parent)
    : QWidget(parent), mCheckedAction(NULL), mOverAction(NULL) {
  setMouseTracking(true);
}

void SideBar::paintEvent(QPaintEvent *event) {
  QPainter p(this);

  QFont fontText(p.font());
  fontText.setFamily("Helvetica Neue");
  p.setFont(fontText);

  int action_y = 0;
  p.fillRect(rect(), QColor(100, 100, 100));
  for (auto action : mActions) {

    QRect actionRect(0, action_y, event->rect().width(), action_height);

    if (action->isChecked()) {
      p.fillRect(actionRect, QColor(35, 35, 35));
    }

    if (action == mOverAction) {
      p.fillRect(actionRect, QColor(150, 150, 150));
    }

    p.setPen(QColor(255, 255, 255));
    QSize size = p.fontMetrics().size(Qt::TextSingleLine, action->text());
    QRect actionTextRect(QPoint(actionRect.width() / 2 - size.width() / 2,
                                actionRect.bottom() - size.height() - 5),
                         size);
    p.drawText(actionTextRect, Qt::AlignCenter, action->text());

    QRect actionIconRect(0, action_y + 10, actionRect.width(),
                         actionRect.height() - 2 * actionTextRect.height() -
                             10);
    QIcon actionIcon(action->icon());
    actionIcon.paint(&p, actionIconRect);

    action_y += actionRect.height();
  }
}

QSize SideBar::minimumSizeHint() const {
  return action_height * QSize(1, mActions.size());
}

void SideBar::addAction(QAction *action) {
  mActions.push_back(action);
  action->setCheckable(true);
  update();
}

QAction *SideBar::addAction(const QString &text, const QIcon &icon) {
  QAction *action = new QAction(icon, text, this);
  action->setCheckable(true);
  mActions.push_back(action);
  update();
  return action;
}

void SideBar::mousePressEvent(QMouseEvent *event) {
  QAction *tempAction = actionAt(event->pos());
  if (tempAction == NULL || tempAction->isChecked())
    return;
  qDebug() << "clicked";
  if (mCheckedAction)
    mCheckedAction->setChecked(false);
  if (mOverAction == tempAction)
    mOverAction = NULL;
  mCheckedAction = tempAction;
  tempAction->setChecked(true);
  update();
  QWidget::mousePressEvent(event);
}

void SideBar::mouseMoveEvent(QMouseEvent *event) {
  QAction *tempAction = actionAt(event->pos());
  if (tempAction == NULL) {
    mOverAction = NULL;
    update();
    return;
  }
  if (tempAction->isChecked() || mOverAction == tempAction)
    return;
  mOverAction = tempAction;
  update();
  QWidget::mouseMoveEvent(event);
}

void SideBar::leaveEvent(QEvent *event) {
  mOverAction = NULL;
  update();
  QWidget::leaveEvent(event);
}

QAction *SideBar::actionAt(const QPoint &at) {
  int action_y = 0;
  for (auto action : mActions) {
    QRect actionRect(0, action_y, rect().width(), action_height);
    if (actionRect.contains(at))
      return action;
    action_y += actionRect.height();
  }
  return NULL;
}

#undef action_height
