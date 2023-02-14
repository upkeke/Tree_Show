#pragma once
#ifndef __MAINWIN__
#define __MAINWIN__

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class BinaryTreeWin;
}
QT_END_NAMESPACE
#include "GrapItemManager.h"
#include <AnimManager.h>
#include <BinaryTreeStr.hpp>
#include <GrapUiManager.h>
#include <NodeTemp.hpp>

class QGraphicsScene;
class QPointF;
class GrapNodeItem;
class QGraphicsLineItem;
class GrapLineItem;
class QGraphicsItem;
class GrapMoveItem;
class QParallelAnimationGroup;
class QPropertyAnimation;
enum class EechOrder;
class MainWin : public QMainWindow {
  Q_OBJECT
public:
  MainWin(QWidget *parent = nullptr);
  template <node_able NodeTy> void set_node_head(NodeTy *head = nullptr) {
    if (head == nullptr) {
      curtree->create_tree();
    } else {
      curtree->init_tree(head);
    }
    // cur_nodeptr_list = curtree->foreach_front();
  }
  void test1();
  ~MainWin();

private:
  void print_tree(sbt::NodePtr head);
  // 如果图元是头节点，会和主窗口有额外的连接
  void headItemConnect(GrapNodeItem *headItem);
  void init_pool();

  _SPC vector<sbt::NodePtr> getListByOrder(EechOrder order);
  Ui::BinaryTreeWin *ui = nullptr;

  //_SPC vector<sbt::NodePtr> cur_nodeptr_list;
  sbt::BinaryTreeStr *curtree = nullptr;
  std::unordered_set<sbt::BinaryTreeStr *> trees{};

  QGraphicsScene *scene = nullptr;
  std::shared_ptr<GrapItemManager> grapPool = nullptr;
  std::shared_ptr<AnimManager> animPool = nullptr;
  std::shared_ptr<GrapUiManager> uiPool = nullptr;
public slots:
  void action_build();
  /**
   * @brief 刷新，恢复节点为黄色
   *
   */
  void action_refresh_color();
  /**
   * @brief 这个根据偏移值修改整棵树的位置，head必须是一棵树的头节点
   *
   * @param head
   * @param offset
   */
  void action_refresh_pos(sbt::NodePtr head, const QPointF &offset);
  void action_add_node();
  void action_leave(bool flag);
  void action_depth(bool flag);
  /**
   * @brief 分裂的新树的头节点
   *
   * @param newHead
   */
  void to_truncate_tree(GrapNodeItem *headItem);
  void changeNodeVal(sbt::NodePtr node);
  /**
   * @brief 头节点是node的树是主树
   *
   * @param node
   */
  void be_main_tree(sbt::NodePtr node);
};

#endif // WIDGET_H
