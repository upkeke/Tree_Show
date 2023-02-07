#include "GrapNodeItem.h"
#include "GrapLineItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QString>
#include <config.h>

namespace {
_string getPixFile(const NodeColor &pix_c) {
  _string str;
  switch (pix_c) {
  case NodeColor::yellow:
    str = "yellow";
    break;
  case NodeColor::red:
    str = "pink";
    break;
  case NodeColor::green:
    str = "green";
    break;
  default:
    break;
  }
#if HAS_QSTRING
  return _string(":/m/img/%1.jpg").arg(str);
#else
  return ":/m/img/" + str + ".jpg";
#endif
}

} // namespace

GrapNodeItem::GrapNodeItem(NodePtr nodeptr, QGraphicsItem *parent)
    : QGraphicsItem{parent}, nodeptr(nodeptr) {
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);

  setPos(QPointF(nodeptr->row, nodeptr->col));
}

void GrapNodeItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->setBrush(nodeptr->color);
  painter->drawEllipse(QPointF(0, 0), radius, radius);

  painter->setPen(pen);

  painter->setFont(QFont("微软雅黑", 15));
#if HAS_QSTRING
  painter->drawText(boundingRect(), Qt::AlignCenter, nodeptr->val);
#else
  painter->drawText(boundingRect(), Qt::AlignCenter,
                    QString::fromStdString(nodeptr->val));

#endif
}

void GrapNodeItem::setVal(const _string &num) {
  nodeptr->val = num;
  nodeptr->val = num;
  scene()->update();
}

void GrapNodeItem::addLine(GrapLineItem *line) { lineArry.push_back(line); }

int GrapNodeItem::reMoveLines() {
  int re = lineArry.size();
  for (auto line : lineArry) {
    line->hide();
  }
  lineArry.clear();
  return re;
}

void GrapNodeItem::clearLines() { lineArry.clear(); }

QRectF GrapNodeItem::boundingRect() const {
  return QRectF(QPointF(-radius, -radius), QSizeF(radius * 2, radius * 2));
}

void GrapNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseMoveEvent(event);
  if (this->isSelected()) {
    nodeptr->setPos(pos());
    this->scene()->update();
  }
}
void GrapNodeItem::setBackColor(NodeColor ncolor) {
  nodeptr->color = ncolor;
  if (nodeptr->color == NodeColor::black)
    this->pen.setColor(Qt::white);
  else
    this->pen.setColor(Qt::black);
}

void GrapNodeItem::reSet(NodePtr nodeptr) {
  this->nodeptr = nodeptr;
}
void GrapNodeItem::setRadius(int radius) {
  this->radius = radius;
}