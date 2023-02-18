

#pragma once
#ifndef __GRAPNODEITEM__
#define __GRAPNODEITEM__

#include <QGraphicsItem>
class GrapLineItem;
#include "Grap_Bin.h"

#include <QPen>
#include <QStrNode.hpp>
#include <config.h>
class QAction;
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
  enum { Type = UserType + 1 };
  int type() const override { return Type; }
  /**
   * @brief 重新设置图元的位置，颜色
   *
   * @param node 根据的节点
   */
  // void reSet(sbt::NodePtr nodeptr);
  sbt::NodePtr getNodePtr();
  void setVal(const QString &num);
  QString strVal() { return val; }
  /**
   * @brief 发现一个直线和图元相连。把它添加到lineArry
   *
   * @param line
   */
  void setChildLines(GrapLineItem *line, bool isLeft);
  void setFatherItem(GrapNodeItem *father);
  GrapNodeItem *getFatherItem();
  /**
   * @brief 清空lineArry，并隐藏
   *
   * @return int
   */
  std::array<GrapLineItem *, 2> reMoveLines();
  GrapLineItem *rmoveLine(bool isLeft);
  /**
   * @brief 清空lineArry，不隐藏
   *
   */
  // void clearLines(); // 这个只是清空lineArry，但不隐藏其中的图元
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
  void SetIsShowDepth(bool flag);
  bool isHeadItem() { return nodePtr == headPtr; }
  void setHeadPtr(sbt::NodePtr head);
  sbt::NodePtr getHeadPtr();
  /**
   * @brief 不会构造menu，
   只是设置nodeptr，和headPtr，然后显示该显示的action
   *
   * @param nodeptr
   * @param headPtr
   */
  void reSet(sbt::NodePtr nodeptr, sbt::NodePtr headPtr);
  ~GrapNodeItem();
signals:
  /**
   * @brief 将sub树合并到main树
   *
   * @param main 树的根节点图元
   * @param sub
   */
  void mergeToOther(GrapNodeItem *main, GrapNodeItem *sub);

  // void updateTreePos(sbt::NodePtr head, const QPointF &offset);

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
  // void addChildNode(bool isLeft, sbt::NodePtr node);
  void deleteNodeItem(GrapNodeItem *headItem);

private:
  /**
   * @brief 禁止外界构造，只能通过GrapItemManager构造
   *
   * @param nodeptr 传入节点指针
   * @param parent
   */
  explicit GrapNodeItem(sbt::NodePtr nodeptr, sbt::NodePtr headPtr,
                        QGraphicsItem *parent = nullptr);
  void initMenu();
  // 只管理和子节点的直线，不管理和父节点的直线，0为左子节点，1为右子节点
  std::array<GrapLineItem *, 2> lineChild{};
  // 连接父节点直线
  GrapNodeItem *fatherItem = nullptr;
  //_SPC vector<GrapLineItem *> lineArry{};
  QPen pen{Qt::black, 2};
  QString val;
  int radius = 15;
  bool isShowDepth = false;
  QMenu *menu = nullptr;
  /**
   * @brief
   actions[0]  "变成主角"
   actions[1]  "截断二叉树"
   actions[2]  "设置值"
   *
   */
  QList<QAction *> actions{4, nullptr};

  sbt::NodePtr headPtr = nullptr;

public:
  sbt::NodePtr nodePtr = nullptr;
};
#endif