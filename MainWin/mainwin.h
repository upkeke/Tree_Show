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
      tree->create_tree();
    } else {
      tree->init_tree(head);
    }
    cur_nodeptr_list = tree->foreach_front();
  }
  void test1();
  ~MainWin();

private:
  void print_tree(sbt::NodePtr head);
  void init_pool();

  void update_cur_nodeptr_list(EechOrder order);

  _SPC vector<sbt::NodePtr> cur_nodeptr_list;
  Ui::BinaryTreeWin *ui = nullptr;
  sbt::BinaryTreeStr *tree = nullptr;

  QGraphicsScene *scene = nullptr;
  std::shared_ptr<GrapItemManager> grapPool = nullptr;
  std::shared_ptr<AnimManager> animPool = nullptr;
  std::shared_ptr<GrapUiManager> uiPool = nullptr;
private slots:
  void action_build_clear(bool flag);
  void action_refresh(bool flag);
  void btn_leave_clicked();
  void btn_reverse_clicked();
  void cb_foreach_change(const QString &str); // btn_leave
};

#endif // WIDGET_H
