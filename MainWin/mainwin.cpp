#include "mainwin.h"
#include "ThScene.h"
#include <FuncForHeadNode.h>
#include <GrapLineItem.h>
#include <GrapMoveItem.h>
#include <GrapNodeItem.h>
#include <GrapUi.h>
#include <QAction>
#include <QDebug>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QLineEdit>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <cmath>
#include <uix_BinaryTreeWin.h>
#include <unordered_set>

using namespace sbt;

QGraphicsItemGroup *getItemGroup(QGraphicsScene *scene) {
  auto x = new QGraphicsItemGroup();
  scene->addItem(x);
  x->setZValue(0.5);
  return x;
}
MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BinaryTreeWin),
      curtree(new sbt::BinaryTreeStr) {
  ui->setupUi(this);
  scene = new ThScene(this);
  ui->view->setScene(scene); // QGraphicsView
  trees[curtree] = getItemGroup(scene);
  ui->view->show();
  init_pool();

  connect(ui->actionbuild, &QAction::triggered, this, &MainWin::action_build);
  connect(ui->actrefresh, &QAction::triggered, this, [this]() {
    auto head = curtree->get_head();
    this->action_refresh_pos(head, head->getOffsetByNowPos());
  });
  connect(ui->actionadd, &QAction::triggered, this, &MainWin::action_add_node);
  connect(ui->actionleaf, &QAction::triggered, this, &MainWin::action_leave);
  connect(ui->actiondepth, &QAction::triggered, this, &MainWin::action_depth);

  // action_leave
}
void MainWin::init_pool() {
  grapPool = GrapItemManager::instance(scene);
  uiPool = GrapUiManager::instance(scene);
  GrapMoveItem *ball = grapPool->getGrapMove(QPointF{-30, -30});
  auto childBtnList = uiPool->ChildBtn();
  animPool = AnimManager::instance(ball, uiPool->ChildBtn(), grapPool);
  UiForeachRootBtn *rootBtn = uiPool->RootBtn();
  // 点击根btn，展开子列表 再次点击是收起
  connect(
      rootBtn, &UiForeachRootBtn::RootBtnPress, this,
      [this](QObject *root) { this->animPool->_遍历列表展开收起动画(root); });
  // 点击遍历按钮，五角星开始遍历动画
  for (auto ptr : childBtnList) {
    connect(ptr, &UiForeachBtn::ChildBtnPress, this,
            [this, rootBtn](EechOrder order) {
              this->animPool->_遍历列表展开收起动画(rootBtn);
              rootBtn->set_order(order);

              // 所有节点颜色恢复
              this->action_refresh_color();
              // this->print_tree(tree->get_head());
              //  开始遍历动画
              animPool->_五角星遍历动画(this->getListByOrder(order));
            });
  }
}
_SPC vector<sbt::NodePtr> MainWin::getListByOrder(EechOrder order) {
  switch (order) {
  case EechOrder::先序:
    return curtree->foreach_front();
  case EechOrder::中序:
    return curtree->foreach_mid();
  case EechOrder::后序:
    return curtree->foreach_back();
  case EechOrder::层级:
    return curtree->foreach_ceng();
  case EechOrder::选择:
    break;
  }
  return {};
}

MainWin::~MainWin() {
  delete ui;
  delete curtree;
}

void MainWin::NodeItemConnect(GrapNodeItem *headItem) {
  // 避免重复连接可以用Qt::UniqueConnection，这儿用另外一个方式，只有是新建的图元才建立连接
  connect(headItem, &GrapNodeItem::truncateCurTree, this,
          &MainWin::to_truncate_tree);

  connect(headItem, &GrapNodeItem::changeVal, this, &MainWin::changeNodeVal);
  if (headItem->isHead) {
    headNodeItemConnect(headItem);
  }
}
void MainWin::headNodeItemConnect(GrapNodeItem *headItem) {
  // connect(headItem, &GrapNodeItem::updateTreePos, this,
  //         &MainWin::action_refresh_pos);
  connect(headItem, &GrapNodeItem::beStar, this, &MainWin::be_main_tree);
  // 只有头节点才具备插入到其他节点后面的能力
  auto new_item = headItem;
  auto new_node = new_item->getNodePtr();
  connect(new_item, &GrapNodeItem::andOther,
          [this, new_item, new_node](QGraphicsItem *other) {
            GrapNodeItem *base_item = qgraphicsitem_cast<GrapNodeItem *>(other);
            if (base_item != nullptr) {
              auto base_node = base_item->getNodePtr();
              // 如果base_node可插入
              if (base_node->left == nullptr || base_node->right == nullptr) {
                using Direction = BinaryTreeStr::Direction;
                Direction dic = Direction::left;
                // 左子树可插入且插入节点的位置位于根节点的左边
                // 可能存在一种情况，base_item的左子树不为空，右子树为空，能进入这儿
                // 但是如果当前节点是在base_item的左边，那么不能连接二者，直接return
                if (new_item->pos().x() <= base_item->pos().x()) {
                  auto bs_tp = base_node->left;
                  if (bs_tp == nullptr) {
                    ;
                    // dirc = Direction::left;
                  } else {
                    return;
                  }
                } else {
                  auto bs_tp = base_node->right;
                  if (bs_tp == nullptr) {
                    dic = Direction::right;
                  } else {
                    return;
                  }
                }
                this->curtree->insert_node(new_node, base_node, dic);
                qDebug() << "我碰到了可插入节点" << base_item->strVal();
                new_item->isHead = false;
                headNodeItemDisConnect(new_item);
                this->grapPool->getGrapLine(base_item, new_item,
                                            dic == Direction::left);
              }
            }
          });
}
void MainWin::headNodeItemDisConnect(GrapNodeItem *headItem) {
  // disconnect(headItem, &GrapNodeItem::updateTreePos, this,
  //            &MainWin::action_refresh_pos);
  disconnect(headItem, &GrapNodeItem::beStar, this, &MainWin::be_main_tree);
}
void MainWin::print_tree(NodePtr head) {
  qDebug() << "print_tree is called ";
  curtree->update_xy();
  std::vector<NodePtr> a节点集合 = curtree->foreach_back();
  if (a节点集合.size() == 0) {
    return;
  }
  for (auto ptr : a节点集合) {
    bool isNew = false;
    GrapNodeItem *curNodeItem =
        grapPool->getGrapNode(ptr, isNew, trees[curtree]);
    if (isNew) {
      NodeItemConnect(curNodeItem);
    }
    // 连接父节点到子节点的线
    grapPool->LineNodeToChild(curNodeItem);
  }
  grapPool->hideSurplus();
  scene->update();
}

void MainWin::action_build() {
  print_tree(curtree->get_head());
  qDebug() << "build";
}
// 所有的节点图元恢复为黄色
void MainWin::action_refresh_color() {
  auto head = curtree->get_head();
  sbt::foreach_front(head, [](NodePtr cur) { cur->color = NodeColor::yellow; });
  head->color = NodeColor::darkMagenta;
  scene->update();
}
void MainWin::action_refresh_pos(NodePtr head, const QPointF &offset) {
  // auto head = curtree->get_head();
  grapPool->updateGrapNodePos(head, offset);
  scene->update();
}

void MainWin::action_add_node() {
  NodePtr new_node = new Node("N");
  // new_node->setColor(NodeColor::cyan);
  new_node->color = Qt::cyan;
  new_node->isHead = true;
  qDebug() << "action_add_node 新建一个node";
  new_node->setPos(QPointF(-60, -60));
  bool f;
  GrapNodeItem *new_item = grapPool->getGrapNode(new_node, f, trees[curtree]);
  new_item->isHead = true;
  NodeItemConnect(new_item);
}
void MainWin::action_leave(bool flag) {
  // 显示叶子，修改叶子的颜色
  auto lefs = curtree->get_leaves();
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
void MainWin::to_truncate_tree(GrapNodeItem *headItem) {

  BinaryTreeStr *ntree = new BinaryTreeStr(headItem->getNodePtr());
  headNodeItemConnect(headItem);
  // 将这棵树
  trees[ntree] = new QGraphicsItemGroup;
  // ntree->update_xy();
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
  for (const auto &[tree, _] : trees) {
    if (tree->get_head() == node) {
      // 上一个主树的颜色回复为普通
      curtree->get_head()->color = NodeColor::yellow;
      // 变成主树
      curtree = tree;
      node->color = NodeColor::darkMagenta;
    }
  }
}
void MainWin::test1() {}