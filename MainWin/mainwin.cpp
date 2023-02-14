#include "mainwin.h"
#include "ui_BinaryTreeWin.h"
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
#include <unordered_set>

using namespace sbt;

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BinaryTreeWin),
      curtree(new sbt::BinaryTreeStr) {
  trees.insert(curtree);
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->view->setScene(scene); // QGraphicsView
  ui->view->show();
  init_pool();
  connect(ui->actionbuild, &QAction::triggered, this, &MainWin::action_build);
  connect(ui->actrefresh, &QAction::triggered, this,
          &MainWin::action_refresh_color);
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
  animPool = AnimManager::instance(ball, uiPool->ChildBtn());
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
              animPool->_五角星遍历动画(this->getListByOrder(order),
                                        this->grapPool);
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
void MainWin::headItemConnect(GrapNodeItem *headItem) {
  connect(headItem, &GrapNodeItem::updateTreePos, this,
          &MainWin::action_refresh_pos);
  connect(headItem, &GrapNodeItem::beStar, this, &MainWin::be_main_tree);
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
    GrapNodeItem *curNodeItem = grapPool->getGrapNode(ptr, isNew);
    if (isNew) {

      // 避免重复连接可以用Qt::UniqueConnection，这儿用另外一个方式，只有是新建的图元才建立连接
      connect(curNodeItem, &GrapNodeItem::truncateCurTree, this,
              &MainWin::to_truncate_tree);

      connect(curNodeItem, &GrapNodeItem::changeVal, this,
              &MainWin::changeNodeVal);
      if (ptr->isHead) {
        headItemConnect(curNodeItem);
      }
    }
    // 连接父节点到子节点的线    beStar
    for (size_t j = 0; j < 2; ++j) {
      NodePtr child = nullptr;
      if (j == 0)
        child = ptr->Left();
      else
        child = ptr->Right();
      if (child != nullptr) {
        QTransform transform;
        QPointF point(child->Pos());
        GrapNodeItem *end =
            qgraphicsitem_cast<GrapNodeItem *>(scene->itemAt(point, transform));
        GrapLineItem *curLineItem = grapPool->getGrapLine(curNodeItem, end);
      }
    }
  }
  grapPool->hideSurplus();
  scene->update();
}

void MainWin::action_build() {
  // flag 初始值是false，在designer的设置，false状态时树图标，true是清空图标
  // 点击后flag会变成true发射过来，再点击变成false
  print_tree(curtree->get_head());
  qDebug() << "build";
  // } else {
  //   curtree->destroy_tree();
  //   grapPool->hideNodes(curtree->foreach_front());
  //   qDebug() << "clear";
  // }
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
  qDebug() << "action_add_node 新建一个node";
  new_node->setPos(QPointF(-60, -60));
  bool f;
  GrapNodeItem *new_item = grapPool->getGrapNode(new_node, f);
  new_item->setIsNew(true);
  connect(new_item, &GrapNodeItem::andOther,
          [this, new_item, new_node](QGraphicsItem *other) {
            GrapNodeItem *base_item = dynamic_cast<GrapNodeItem *>(other);
            if (base_item != nullptr) {
              auto base_node = base_item->getNodePtr();
              // 如果base_node可插入
              if (base_node->Left() == nullptr ||
                  base_node->Right() == nullptr) {
                using Direction = BinaryTreeStr::Direction;

                // 左子树可插入且插入节点的位置位于根节点的左边
                if (new_item->pos().x() <= base_item->pos().x()) {
                  auto bs_tp = base_node->Left();
                  if (bs_tp == nullptr) {
                    this->curtree->insert_node(new_node, base_node,
                                               Direction::left);
                    // dirc = Direction::right;
                  } else {
                    return;
                  }
                } else {
                  auto bs_tp = base_node->Right();
                  if (bs_tp == nullptr) {
                    this->curtree->insert_node(new_node, base_node,
                                               Direction::right);
                    // dirc = Direction::right;
                  } else {
                    return;
                  }
                }
                qDebug() << "我碰到了可插入节点"
                         << QString::fromStdString(base_item->strVal());
                new_item->setIsNew(false);
                this->grapPool->getGrapLine(base_item, new_item);
              }
            }
          });
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
  headItemConnect(headItem);
  trees.insert(ntree);
  // ntree->update_xy();
}
void MainWin::changeNodeVal(NodePtr node) {
  bool ok;
  QString text = QInputDialog::getText(this, tr("Enter text"), tr("Text:"),
                                       QLineEdit::Normal, QString(), &ok);
  if (ok && !text.isEmpty()) {
    node->val = text.toStdString();
  }
  scene->update();
}
void MainWin::be_main_tree(sbt::NodePtr node) {
  node->color = NodeColor::darkMagenta;
  for (auto tree : trees) {
    if (tree->get_head() == node)
      curtree = tree;
  }
}
void MainWin::test1() {}