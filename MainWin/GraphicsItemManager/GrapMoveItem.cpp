
#include "GrapMoveItem.h"
#include <QPainter>
#include <QMenu>
#include<QGraphicsSceneContextMenuEvent>
QList<QPointF> getPoints(qreal r) {
  qreal rprime = r * sin(18 * M_PI / 180) / sin(126 * M_PI / 180);
  QPointF A{r * cos(18 * M_PI / 180), r * sin(18 * M_PI / 180)};
  QPointF B{r * cos(90 * M_PI / 180), r * sin(90 * M_PI / 180)};
  QPointF C{r * cos(162 * M_PI / 180), r * sin(162 * M_PI / 180)};
  QPointF D{r * cos(234 * M_PI / 180), r * sin(234 * M_PI / 180)};
  QPointF E{r * cos(306 * M_PI / 180), r * sin(306 * M_PI / 180)};
  QPointF F{rprime * cos(54 * M_PI / 180), rprime * sin(54 * M_PI / 180)};
  QPointF G{rprime * cos(126 * M_PI / 180), rprime * sin(126 * M_PI / 180)};
  QPointF H{rprime * cos(198 * M_PI / 180), rprime * sin(198 * M_PI / 180)};
  QPointF I{rprime * cos(270 * M_PI / 180), rprime * sin(272 * M_PI / 180)};
  QPointF J{rprime * cos(342 * M_PI / 180), rprime * sin(342 * M_PI / 180)};
  QList<QPointF> points{B, F, A, J, E, I, D, H, C, G};
  return points;
}
_SPC vector<QPointF> getPentagonPoints(qreal radius) {
  _SPC vector<QPointF> points;
  for (int i = 0; i < 5; ++i) {
    qreal angle = 2 * M_PI / 5 * i;
    QPointF(QPointF(radius * cos(angle), radius * sin(angle)));
  }
  return points;
}
GrapMoveItem::GrapMoveItem(QPointF mPos, QGraphicsItem *parent)
    : QGraphicsItem(parent), wu(getPoints(radius)) {
  setPos(mPos);
  setZValue(3);
}
void GrapMoveItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->setBrush(Qt::red);
  painter->setPen(Qt::black);
  painter->drawPolygon(wu.data(), 10); // 画五角星
}
QRectF GrapMoveItem::boundingRect() const {
  return QRectF(QPointF(-radius, -radius), QSizeF(radius * 2, radius * 2));
}
QPainterPath GrapMoveItem::shape()const {
  QPainterPath path;
  path.addPolygon(wu);
  return path;
}
void GrapMoveItem::setRadius(int radius) {
  this->radius = radius;
  wu = getPoints(radius);
}
void GrapMoveItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  menu.addAction("Action 1");
  menu.addAction("Action 2");
  menu.exec(event->screenPos());
}