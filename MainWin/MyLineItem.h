//author : keke
//date : 2023/01/30 
#pragma once
#ifndef __MYLINEITEM__
#define __MYLINEITEM__

#include <QGraphicsLineItem>
class MyGraphicsItem;

// coordinate
class MyLineItem : public QGraphicsLineItem {
public:
  MyLineItem(MyGraphicsItem *front, MyGraphicsItem *end,
             QGraphicsItem *parent = nullptr);
  void setTwo(MyGraphicsItem *, MyGraphicsItem *);

private:
  MyGraphicsItem *front;
  MyGraphicsItem *end;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
};
#endif
