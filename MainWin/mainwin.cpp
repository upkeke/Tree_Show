#include "mainwin.h"
#include "ui_mainwin.h"
#include <GrapLineItem.h>
#include <GrapMoveItem.h>
#include <GrapNodeItem.h>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <cmath>

qreal disBtwItem(const QPointF &p1, const QPointF &p2) {
  auto p = p1 - p2;

  return std::sqrt(p.rx() * p.rx() + p.y() * p.y());
}

MainWin::MainWin(QWidget *parent)
    : QWidget(parent), ui(new Ui::mainwin), tree(new BinaryTreeStr) {
  ui->setupUi(this);
  init_win();
  ui->view->setScene(scene); // QGraphicsView
  ui->view->show();
  connect(ui->btn_build, &QPushButton::clicked, this,
          &MainWin::btn_build_clicked);
  connect(ui->btn_reverse, &QPushButton::clicked, this,
          &MainWin::btn_reverse_clicked);
  connect(ui->btn_foreach, &QPushButton::clicked, this,
          &MainWin::btn_foreach_clicked);
  connect(ui->btn_leave, &QPushButton::clicked, this,
          &MainWin::btn_leave_clicked);
  connect(ui->cb_foreach, &QComboBox::currentTextChanged, this,
          &MainWin::cb_foreach_change);
}
void MainWin::init_win() {
  scene = new QGraphicsScene(this);
  grapPool = GrapItemManager::instance(scene);
  GrapMoveItem *ball = grapPool->getGrapMove(QPointF{-30, -30});
  move_group = new QParallelAnimationGroup(this);
  QPropertyAnimation *am1 = new QPropertyAnimation(ball, "pos");
  QPropertyAnimation *am2 = new QPropertyAnimation(ball, "rotation");
  move_group->addAnimation(am1);
  move_group->addAnimation(am2);

  connect(am1, &QPropertyAnimation::valueChanged, this,
          [this, curIndex = 0](const QVariant &value) mutable {
            if (curIndex < cur_nodeptr_list.size()) {
              qreal dis = disBtwItem(cur_nodeptr_list[curIndex]->Pos(),
                                     value.toPointF());
              if (dis < 20) {
                cur_nodeptr_list[curIndex]->setColor(NodeColor::green);
                // 当五角星靠近图元节点的时候放大节点图元，然后复原
                QPropertyAnimation *tpanm = new QPropertyAnimation(
                    this->grapPool->whereGrapNode(cur_nodeptr_list[curIndex]),
                    "scale");
                tpanm->setDuration(1000);
                tpanm->setStartValue(1.0);
                tpanm->setKeyValueAt(0.5, 1.5);
                tpanm->setEndValue(1.0);
                tpanm->setEasingCurve(QEasingCurve::OutBounce);
                connect(tpanm, &QPropertyAnimation::currentLoopChanged, tpanm,
                        [tpanm](int currentLoop) {
                          if (currentLoop == 1) {
                            tpanm->setDirection(QPropertyAnimation::Backward);
                          }
                        });
                curIndex++;
                tpanm->start(QPropertyAnimation::DeleteWhenStopped);
              }
            } else {
              curIndex = 0;
            }
            this->scene->update();
          });
}

MainWin::~MainWin() {
  delete ui;
  delete tree;
}

void MainWin::print_tree(NodePtr head) {
  qDebug() << "print_tree is called ";
  std::vector<NodePtr> a节点集合 = tree->foreach_back();
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

void MainWin::btn_build_clicked() { print_tree(tree->head); }

void MainWin::btn_reverse_clicked() {
  this->tree->reverse_tree();
  cb_foreach_change(ui->cb_foreach->currentText());
  this->print_tree(this->tree->head);
}
void MainWin::btn_foreach_clicked() {
  // 控制坐标
  QPropertyAnimation *am1 =
      static_cast<QPropertyAnimation *>(move_group->animationAt(0));
  QPropertyAnimation *am2 =
      static_cast<QPropertyAnimation *>(move_group->animationAt(1));
  am1->setDuration(10000);
  am1->setStartValue(QPointF{-30, -30});
  am1->setEndValue(QPointF{-30, -30});
  am2->setDuration(10000);
  am2->setStartValue(0);
  am2->setEndValue(1800);
  int sz = cur_nodeptr_list.size();
  for (double i = 1; i <= sz; ++i) {
    am1->setKeyValueAt(i / (sz + 1), cur_nodeptr_list[i - 1]->Pos());
  }
  move_group->start();
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
