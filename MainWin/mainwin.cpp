#include "mainwin.h"
#include "ThScene.h"
#include "settingWin.h"
#include <FuncForHeadNode.h>
#include <GrapLineItem.h>
// #include <GrapMoveItem.h>
#include <GrapNodeItem.h>
// #include <GrapUi.h>
#include <QAction>
#include <QDebug>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QLineEdit>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <cmath>
#include <iostream>
#include <uix_BinaryTreeWin.h>
#include <unordered_set>

using namespace sbt;

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BinaryTreeWin) {
  ui->setupUi(this);
  scene = new ThScene(this);
  ui->view->setScene(scene);
  ui->view->show();

  init_pool();
  // 设置窗口
  setWin = new SettingWin();
  setWin->hide();
  // 建立二叉树
  connect(ui->actionbuild, &QAction::triggered, this, &MainWin::action_build);
  // 调整二叉树的每个节点的位置
  connect(ui->actrefresh, &QAction::triggered, this, [this]() {
    for (auto head : trees) {
      this->grapPool->updateGrapNodePos(head);
    }
    scene->update();
  });
  // 添加节点
  connect(ui->actionadd, &QAction::triggered, this, &MainWin::action_add_node);
  // 显示叶子
  connect(ui->actionleaf, &QAction::triggered, this, &MainWin::action_leave);
  // 显示深度
  connect(ui->actiondepth, &QAction::triggered, this, &MainWin::action_depth);
  // 显示设置按钮
  connect(ui->actionset, &QAction::triggered, setWin, &SettingWin::show);

  // action_leave
  connect(setWin, &SettingWin::buildTree, this, &MainWin::add_new_tree);
}
void MainWin::init_pool() {
  grapPool = GrapItemManager::instance(scene, trees, curtree);
  animPool = AnimManager::instance(grapPool);
  animPool->setHeadNode(&curtree);
}

MainWin::~MainWin() {
  delete ui;
  for (auto i : trees)
    deleteTree(i);
  // delete curtree;
}

void MainWin::print_tree(NodePtr headptr) {
  qDebug() << "print_tree is called ";
  std::vector<NodePtr> a节点集合 = foreach_back_v(headptr);
  if (a节点集合.size() == 0) {
    return;
  }
  for (auto ptr : a节点集合) {
    bool isNew = false;
    GrapNodeItem *curNodeItem = grapPool->getGrapNode(ptr, isNew, headptr);
    // 连接父节点到子节点的线
    grapPool->LineNodeToChild(curNodeItem);
  }
  scene->update();
}

void MainWin::action_build() {
  print_tree(curtree);
  qDebug() << "build";
}

void MainWin::action_add_node() {
  NodePtr new_node = new Node("N");
  new_node->color = Qt::cyan;
  qDebug() << "action_add_node 新建一个node";
  new_node->setPos(QPointF(-60, -60));
  bool f{};
  GrapNodeItem *sub_item = grapPool->getGrapNode(new_node, f, new_node);
  grapPool->reSetTreeNodeItemHead(sub_item, sub_item->getNodePtr());
}
void MainWin::action_leave(bool flag) {
  // 显示叶子，修改叶子的颜色
  auto lefs = get_leaves_v(curtree);
  for (auto i : lefs) {
    if (flag)
      i->color = NodeColor::magenta;
    else
      i->color = NodeColor::yellow;
  }
  scene->update();
}
void MainWin::action_depth(bool flag) {
  // 显示深度
  if (flag) {
    grapPool->ShowDepthOrVal(true);
  } else { // 显示val
    grapPool->ShowDepthOrVal(false);
  }
  scene->update();
}
void MainWin::add_new_tree(sbt::NodePtr headptr) {
  // 加入到集合中
  trees.insert(headptr);
  print_tree(headptr);
}
