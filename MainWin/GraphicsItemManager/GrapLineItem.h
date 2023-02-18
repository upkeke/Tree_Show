// author : keke
// date : 2023/01/30
#pragma once
#ifndef __MYLINEITEM__
#define __MYLINEITEM__
#include "Grap_Bin.h"
#include <QGraphicsLineItem>
#include <array>

class GrapNodeItem;

/**
 * @brief 直线图元节点
 2个成员变量是是直线2段的树节点
 *
 */
class GRAP_LIB_EXPORT GrapLineItem : public QGraphicsLineItem {
public:
  GrapLineItem(GrapNodeItem *father, GrapNodeItem *child,bool isLeft,
               QGraphicsItem *parent = nullptr);
  void setTwo(GrapNodeItem *father, GrapNodeItem *child,bool isLeft);
  bool isLeftLine();
  void setIsLeftLine(bool isleft);
  std::array<GrapNodeItem *, 2> getFrontEnd() { return {father, child}; }

private:
  GrapNodeItem *father;
  GrapNodeItem *child;
  bool isleft = true;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
};
#endif
