#include "mainwin.h"
#include "ui_BinaryTreeWin.h"
#include <GrapLineItem.h>
#include <GrapMoveItem.h>
#include <GrapNodeItem.h>
#include <GrapUi.h>
#include <QAction>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <cmath>

using namespace sbt;

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BinaryTreeWin),
      tree(new sbt::BinaryTreeStr) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  // test1();
  ui->view->setScene(scene); // QGraphicsView
  ui->view->show();
  init_pool();
  connect(ui->actionbuild, &QAction::triggered, this,
          &MainWin::action_build_clear);
  connect(ui->actrefresh, &QAction::triggered, this,
          &MainWin::action_build_clear);
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
              // 开始遍历
              this->update_cur_nodeptr_list(order);
              // this->print_tree(tree->get_head());
              //  开始遍历动画
              animPool->_五角星遍历动画(this->cur_nodeptr_list, this->grapPool);
            });
  }
  // ui->view->init_Ui(rootBtn);
}
void MainWin::update_cur_nodeptr_list(EechOrder order) {
  cur_nodeptr_list.clear();
  switch (order) {
  case EechOrder::先序:
    cur_nodeptr_list = tree->foreach_front();
    break;
  case EechOrder::中序:
    cur_nodeptr_list = tree->foreach_mid();
    break;
  case EechOrder::后序:
    cur_nodeptr_list = tree->foreach_back();
    break;
  case EechOrder::层级:
    cur_nodeptr_list = tree->foreach_ceng();
    break;
  case EechOrder::选择:
    break;
  }
}

MainWin::~MainWin() {
  delete ui;
  delete tree;
}

void MainWin::print_tree(NodePtr head) {
  qDebug() << "print_tree is called ";
  std::vector<NodePtr> a节点集合 = tree->foreach_back();
  if (a节点集合.size() == 0) {
    return;
  }
  for (auto ptr : a节点集合) {
    GrapNodeItem *curNodeItem = grapPool->getGrapNode(ptr);
    // 连接父节点到子节点的线
    for (size_t j = 0; j < 2; ++j) {
      NodePtr child = nullptr;
      if (j == 0)
        child = ptr->Left();
      else
        child = ptr->Right();
      if (child != nullptr) {
        QTransform transform;
        QPointF point(child->row, child->col);
        GrapNodeItem *end =
            qgraphicsitem_cast<GrapNodeItem *>(scene->itemAt(point, transform));
        GrapLineItem *curLineItem = grapPool->getGrapLine(curNodeItem, end);
        // 由于直线与2个图元连接，把直线添加到2个图元中
        curNodeItem->addLine(curLineItem);
        end->addLine(curLineItem);
      }
    }
  }
  grapPool->hideSurplus();
  scene->update();
}

void MainWin::action_build_clear(bool flag) {
  // flag 初始值是false，在designer的设置，false状态时树图标，true是清空图标
  // 点击后flag会变成true发射过来，再点击变成false
  if (flag) {
    print_tree(tree->head);
    qDebug() << "build";
  } else {
    tree->destroy_tree();
    ;
    cur_nodeptr_list.clear();
    grapPool->hideAll();
    qDebug() << "clear";
  }
}
void MainWin::action_refresh(bool flag) {
  
  animPool->_五角星遍历动画(cur_nodeptr_list, grapPool);
}

void MainWin::btn_reverse_clicked() {
  // this->tree->reverse_tree();
  // cb_foreach_change(ui->cb_foreach->currentText());
  // this->print_tree(this->tree->head);
}
void MainWin::btn_leave_clicked() {
  auto arr = tree->get_leaves();
  for (auto ptr : arr) {
    ptr->setColor(Qt::cyan);
    scene->update();
  }
}
void MainWin::cb_foreach_change(const QString &str) {
  cur_nodeptr_list.clear();
  if (str == "前序") {
    cur_nodeptr_list = tree->foreach_front();
  } else if (str == "中序") {
    cur_nodeptr_list = tree->foreach_mid();
  } else if (str == "后序") {
    cur_nodeptr_list = tree->foreach_back();
  } else {
    cur_nodeptr_list = tree->foreach_ceng();
  }
  // 复原
  for (auto x : cur_nodeptr_list) {
    x->setColor(Qt::yellow);
  }
  scene->update();
}
void MainWin::test1() {}