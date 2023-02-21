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
#include<GrapItemManager.h>
#include <AnimManager.h>
#include <HeadNode.h>
#include <QStrNode.hpp>

class ThScene;
class SettingWin;
enum class EechOrder;
class MainWin : public QMainWindow {
  Q_OBJECT
public:
  MainWin(QWidget *parent = nullptr);
  template <node_able NodeTy> void set_node_head(NodeTy *head = nullptr) {
    if (head == nullptr) {
      this->curtree = sbt::create_tree();
    } else {
      this->curtree = sbt::init_tree(head);
    }
    this->curtree->color = sbt::NodeColor::magenta;
    this->trees.insert(curtree);
  }
  ~MainWin();
signals:
  void sendHeadnode(sbt::NodePtr tree);

private:
  void print_tree(sbt::NodePtr tree);
  /// 节点图元和this建立连接
  void NodeItemConnect(GrapNodeItem *headItem);
  // 如果图元是头节点，会和主窗口有额外的连接
  void headNodeItemConnect(GrapNodeItem *headItem);
  void init_pool();
  void deleteTree(sbt::NodePtr tree);

  _SPC vector<sbt::NodePtr> getListByOrder(EechOrder order);
  Ui::BinaryTreeWin *ui = nullptr;

  sbt::NodePtr curtree = nullptr;
  // 每颗树的所有节点图元都保存在一个中,为了快速删除
  std::unordered_set<sbt::NodePtr> trees{};

  ThScene *scene = nullptr;
  std::shared_ptr<GrapItemManager> grapPool = nullptr;
  std::shared_ptr<AnimManager> animPool = nullptr;
  // std::shared_ptr<GrapUiManager> uiPool = nullptr;
  SettingWin *setWin;
public slots:
  void action_build();
  /**
   * @brief 这个根据偏移值修改整棵树的位置，head必须是一棵树的头节点
   *
   * @param head
   */
 // void action_refresh_pos(sbt::NodePtr head);
  void action_add_node();
  void action_leave(bool flag);
  void action_depth(bool flag);
  /**
   * @brief 根据树节点添加一颗新树
   如果先序 中序 的数据后构建新树
   *
   * @param headptr
   */
  void add_new_tree(sbt::NodePtr headptr);
  //void changeNodeVal(sbt::NodePtr node);

};

#endif // WIDGET_H
