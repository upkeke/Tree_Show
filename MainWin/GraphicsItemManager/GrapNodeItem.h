// author : keke
// date : 2023/01/30
#pragma once
#ifndef __MYGRAPHICSITEM__
#define __MYGRAPHICSITEM__

#include <QGraphicsItem>
class GrapLineItem;
#include <BinaryTree.hpp>
#include <QPen>
#include <config.h>

#ifndef NODECOLOR
#define NODECOLOR
enum class NodeColor {
  yellow,
  green,
  pink,
  black,
};
#endif
using NodePtr = PosStrNode*;
class GrapNodeItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  Q_PROPERTY(_string val READ getVal WRITE setVal)
public:
  // https://blog.csdn.net/kenfan1647/article/details/116991074

  explicit GrapNodeItem(NodePtr nodeptr,
                        QGraphicsItem *parent = nullptr);
  /**
   * @brief 重新设置图元的位置，颜色
   *
   * @param node 根据的节点
   */
  void reSet(NodePtr nodeptr);
  void setVal(const QString &num);
  QString getVal();
  void addLine(GrapLineItem *);
  int reMoveLines(); // 与当前图元连接的直线图元全部隐藏，并返回移出的个数
  void clearLines(); // 这个只是清空lineArry，但不隐藏其中的图元
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void setBackColor(NodeColor pix_c);
  void advance(int phase) override;
  /**
   * @brief 设置图元的实际宽
   * 图片传进来后会进行收缩，这个变量是缩放后图元的宽
   * @param order_h
   */
  void toHeight(int order_h = 30);

private:
  // QPointF lt{0, 0}; // 左上角的坐标 相对于自己的坐标系
  QPixmap pix;                            // 图元的背景图片
  _SPC vector<GrapLineItem *> lineArry{}; // 与当前图元连接的图元集合
  QPen pen{Qt::black};
  NodePtr nodeptr = nullptr;
  _string val;
};
#endif