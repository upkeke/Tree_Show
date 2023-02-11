

#pragma once
#ifndef __GRAPNODEITEM__
#define __GRAPNODEITEM__

#include <QGraphicsItem>
class GrapLineItem;
#include <NodeStr.hpp>
#include <QPen>
#include <config.h>
#include"Grap_Bin.h"

class GRAP_LIB_EXPORT GrapNodeItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  /**
   * @brief 添加缩放属性
   *
   * @param setScale
   */
  Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
  friend class GrapItemManager;
  /**
   * @brief 重新设置图元的位置，颜色
   *
   * @param node 根据的节点
   */
  void reSet(sbt::NodePtr nodeptr);
  void setVal(const _string &num);
  _string strVal() { return val; }
  /**
   * @brief 发现一个直线和图元相连。把它添加到lineArry
   *
   * @param line
   */
  void addLine(GrapLineItem *line);
  /**
   * @brief 清空lineArry，并隐藏
   *
   * @return int
   */
  int reMoveLines();
  /**
   * @brief 清空lineArry，不隐藏
   *
   */
  void clearLines(); // 这个只是清空lineArry，但不隐藏其中的图元
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

  /**
   * @brief Set the Back Color
   *
   * @param col
   */
  void setBackColor(sbt::NodeColor col);
  /**
   * @brief 设置图元的实际宽
   * 图片传进来后会进行收缩，这个变量是缩放后图元的宽
   * @param order_h
   */
  void setRadius(int order_h = 30);
signals:
/**
 * @brief 碰到其他图元发射其他图元
 * 
 * @param other 
 */
  void andOther(QGraphicsItem *other);

private:
  /**
   * @brief 禁止外界构造，只能通过GrapItemManager构造
   *
   * @param nodeptr 传入节点指针
   * @param parent
   */
  explicit GrapNodeItem(sbt::NodePtr nodeptr, QGraphicsItem *parent = nullptr);

  /**
   * @brief 与节点图元连接的直线图元
   *
   */
  _SPC vector<GrapLineItem *> lineArry{};
  QPen pen{Qt::black};
  sbt::NodePtr nodeptr = nullptr;
  _string val;
  int radius = 15;
};
#endif