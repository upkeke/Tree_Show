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
  ui->view->setScene(scene); // QGraphicsView
  ui->view->show();

  init_pool();
  // 设置窗口
  setWin = new SettingWin();
  setWin->hide();

  connect(ui->actionbuild, &QAction::triggered, this, &MainWin::action_build);
  connect(ui->actrefresh, &QAction::triggered, this, [this]() {
    for (auto head : trees) {

      this->grapPool->updateGrapNodePos(head);
      scene->update();
      // this->action_refresh_pos(head);
    }
  });
  connect(ui->actionadd, &QAction::triggered, this, &MainWin::action_add_node);
  connect(ui->actionleaf, &QAction::triggered, this, &MainWin::action_leave);
  connect(ui->actiondepth, &QAction::triggered, this, &MainWin::action_depth);
  connect(ui->actionset, &QAction::triggered, this,
          [this]() { setWin->show(); });

  // action_leave
  connect(setWin, &SettingWin::buildTree, this, &MainWin::add_new_tree);
}
void MainWin::init_pool() {
  grapPool = GrapItemManager::instance(scene);
  animPool = AnimManager::instance(grapPool);
  animPool->setHeadNode(&curtree);
}
void MainWin::deleteTree(sbt::NodePtr tree) {
  sbt::delete_tree(tree);
  trees.erase(tree);
}

MainWin::~MainWin() {
  delete ui;
  delete curtree;
}

void MainWin::NodeItemConnect(GrapNodeItem *headItem) {
  // 分裂成一颗新树
  connect(headItem, &GrapNodeItem::truncateCurTree, this,
          [this](GrapNodeItem *curItem) {
            grapPool->disconnectGrapNode(curItem->getFatherItem(), curItem);
            // 加入到集合中
            trees.insert(curItem->getNodePtr());
            scene->update();
          });
  // 修改值
  connect(headItem, &GrapNodeItem::changeVal, this, &MainWin::changeNodeVal);
  connect(headItem, &GrapNodeItem::deleteNodeItem, this,
          [this](GrapNodeItem *headItem) {
            grapPool->deleteTree(headItem);
            trees.erase(headItem->getNodePtr());
          });
  headNodeItemConnect(headItem);
}
void MainWin::headNodeItemConnect(GrapNodeItem *headItem) {
  connect(headItem, &GrapNodeItem::beStar, this, &MainWin::be_main_tree);
  // 只有头节点才具备插入到其他节点后面的能力，合并的能力
  connect(headItem, &GrapNodeItem::mergeToOther, this,
          [this](GrapNodeItem *main_item, GrapNodeItem *sub_item) {
            trees.erase(sub_item->getNodePtr());
            this->grapPool->mergeTree(main_item, sub_item);
          });
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
    if (isNew) {
      NodeItemConnect(curNodeItem);
    }
    // 连接父节点到子节点的线
    grapPool->LineNodeToChild(curNodeItem);
  }
  // grapPool->hideSurplus();
  scene->update();
}

void MainWin::action_build() {
  print_tree(curtree);
  qDebug() << "build";
}

// // ui->actrefresh 的点击信号
// void MainWin::action_refresh_pos(NodePtr head) {
//   // auto head = curtree->get_head();
//   grapPool->updateGrapNodePos(head);
//   scene->update();
// }

void MainWin::action_add_node() {
  NodePtr new_node = new Node("N");
  // new_node->setColor(NodeColor::cyan);
  new_node->color = Qt::cyan;
  qDebug() << "action_add_node 新建一个node";
  new_node->setPos(QPointF(-60, -60));
  bool f{};
  GrapNodeItem *sub_item = grapPool->getGrapNode(new_node, f, new_node);
  grapPool->reSetTreeNodeItemHead(sub_item, sub_item->getNodePtr());
  NodeItemConnect(sub_item);
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
void MainWin::changeNodeVal(NodePtr node) {
  bool ok;
  QString text = QInputDialog::getText(this, tr("Enter text"), tr("Text:"),
                                       QLineEdit::Normal, QString(), &ok);
  if (ok && !text.isEmpty()) {
    node->val = text;
  }
  scene->update();
}
void MainWin::be_main_tree(sbt::NodePtr node) {
  node->color = NodeColor::yellow;
  curtree = node;
}

void MainWin::test1() {}