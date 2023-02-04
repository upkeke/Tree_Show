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

  setZValue(this->front->zValue() - 1);     // 让线的图层 在front的下面
  setFlag(QGraphicsItem::ItemIsSelectable); // 线段可选择的
  // QPen(Qt::red, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
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

// https://blog.csdn.net/qq_32046111/article/details/121565965
// https://blog.csdn.net/Fallinlove520/article/details/105727096
void GrapLineItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  if (front->collidesWithItem(end))
    return;
  painter->setPen(this->pen());
  painter->drawLine(front->pos(), end->pos());
}
