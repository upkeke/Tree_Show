#include "GrapLineItem.h"
#include "GrapNodeItem.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
GrapLineItem::GrapLineItem(GrapNodeItem *father, GrapNodeItem *child,
                           bool isLeft, QGraphicsItem *parent)
    : QGraphicsLineItem{parent}, father(father), child(child) {

  setTwo(father, child, isLeft);
  setZValue(-1); // 让线的图层 在front的下面
}

void GrapLineItem::setTwo(GrapNodeItem *father, GrapNodeItem *child,
                          bool isLeft) {
  if (father == nullptr || child == nullptr) {
    qDebug() << "GrapLineItem::setTwo itemAt没找到图元2";
    return;
  }
  
  this->father = father;
  this->child = child;
  this->child->setFatherItem(father);
  this->father->setChildLines(this, isLeft);
  setIsLeftLine(isLeft);
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
  if (father->collidesWithItem(child))
    return;
  painter->setPen(this->pen());
  painter->drawLine(father->pos(), child->pos());
}
