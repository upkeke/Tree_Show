#include "GrapLineItem.h"
#include "GrapNodeItem.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
GrapLineItem::GrapLineItem(GrapNodeItem *front, GrapNodeItem *end,
                           QGraphicsItem *parent)
    : QGraphicsLineItem{parent}, front(front), end(end) {
  if (front == nullptr || end == nullptr) {
    qDebug() << "itemAt没找到图元1";
    return;
  }
  setZValue(-1);                            // 让线的图层 在front的下面
  //setFlag(QGraphicsItem::ItemIsSelectable); // 线段可选择的
  QPen pen(Qt::red);

  pen.setWidth(3);
  setPen(pen);
}

void GrapLineItem::setTwo(GrapNodeItem *one, GrapNodeItem *two) {
  if (front == nullptr || end == nullptr)
    qDebug() << "itemAt没找到图元2";
  front = one;
  end = two;
}
bool GrapLineItem::isLeftLine() { return isleft; }
void GrapLineItem::setIsLeftLine(bool isleft) {
  QColor color;
  QPen pen(color);
  pen.setWidth(3);
  if (isleft) {
    pen.setColor(QColor("#73FA64")); // 浅绿
    // QColor gr("#73FA64");
  } else {
    pen.setColor(QColor("#FF6666")); // 淡红
  }
  this->setPen(pen);
  this->isleft = isleft;
}
void GrapLineItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  if (front->collidesWithItem(end))
    return;
  painter->setPen(this->pen());
  painter->drawLine(front->pos(), end->pos());
}
