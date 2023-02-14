

#pragma once
#ifndef __GRAPNODEITEM__
#define __GRAPNODEITEM__

#include <QGraphicsItem>
class GrapLineItem;
#include "Grap_Bin.h"
#include <NodeStr.hpp>
#include <QPen>
#include <config.h>
class MainWin;
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
  sbt::NodePtr getNodePtr();
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

  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
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
  void setIsNew(bool flag);
  void SetIsShowDepth(bool flag);
  ~GrapNodeItem();
signals:
  /**
   * @brief 碰到其他图元发射其他图元
   *
   * @param other
   */
  void andOther(QGraphicsItem *other);
  /**
   * @brief 更新树的所有节点的场景位置
   *
   */
  void updateTreePos(sbt::NodePtr head, const QPointF &offset);
  /**
   * @brief 截断二叉树，当前选中节点作为新的树的根节点
   *
   */
  void truncateCurTree(GrapNodeItem *headItem);
  /**
   * @brief 修改节点的值
   *
   * @param node
   */
  void changeVal(sbt::NodePtr node);
  /**
   * @brief 作为主树，场景中可能有很多树，当前这个被作为被遍历的树
   *
   * @param node
   */
  void beStar(sbt::NodePtr node);
  void addChildNode(bool isLeft, sbt::NodePtr node);

private:
  /**
   * @brief 禁止外界构造，只能通过GrapItemManager构造
   *
   * @param nodeptr 传入节点指针
   * @param parent
   */
  explicit GrapNodeItem(sbt::NodePtr nodeptr, QGraphicsItem *parent = nullptr);
  void initMenu();
  /**
   * @brief 如果是根节点会有更多的action
   * 
   */
  void actionOnlyHead();

  _SPC vector<GrapLineItem *> lineArry{};
  QPen pen{Qt::black};
  sbt::NodePtr nodeptr = nullptr;
  _string val;
  int radius = 15;
  bool isNew = false;
  bool isShowDepth = false;
  QMenu *menu = nullptr;
};
#endif