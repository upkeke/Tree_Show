#pragma once
#ifndef __MAINWIN__
#define __MAINWIN__

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class mainwin;
}
QT_END_NAMESPACE
#include "GrapItemManager.h"
#include <BinaryTreeStr.hpp>
class QGraphicsScene;
class QPointF;
class GrapNodeItem;
class QGraphicsLineItem;
class GrapLineItem;
class QGraphicsItem;
class GrapMoveItem;
class QParallelAnimationGroup;
class QPropertyAnimation;
class MainWin : public QWidget {
  Q_OBJECT
public:
  MainWin(QWidget *parent = nullptr);
  template <str_able tp = int>
  void set_node_head(_baseNode<tp> *head = nullptr) {
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
  void print_tree(NodePtr head);
  void init_win();

  _SPC vector<NodePtr> cur_nodeptr_list;
  Ui::mainwin *ui = nullptr;
  BinaryTreeStr *tree = nullptr;

  QGraphicsScene *scene = nullptr;
  std::shared_ptr<GrapItemManager> grapPool = nullptr;
  /**
   * @brief 五角星的移动动画
   目前限定五角星只有2个动作，禁止随意添加动作
   *
   */
  QParallelAnimationGroup *move_group = nullptr;

private slots:
  void btn_build_clicked();
  void btn_foreach_clicked();
  void btn_leave_clicked();
  void btn_reverse_clicked();
  void cb_foreach_change(const QString &str);//btn_leave
};

#endif // WIDGET_H
