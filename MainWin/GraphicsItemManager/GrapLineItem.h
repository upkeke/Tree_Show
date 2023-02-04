//author : keke
//date : 2023/01/30 
#pragma once
#ifndef __MYLINEITEM__
#define __MYLINEITEM__

#include <QGraphicsLineItem>
class GrapNodeItem;

// coordinate
class GrapLineItem : public QGraphicsLineItem {
public:
  GrapLineItem(GrapNodeItem *front, GrapNodeItem *end,
             QGraphicsItem *parent = nullptr);
  void setTwo(GrapNodeItem *, GrapNodeItem *);

private:
  GrapNodeItem *front;
  GrapNodeItem *end;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
};
#endif
