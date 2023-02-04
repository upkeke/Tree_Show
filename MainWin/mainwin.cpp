#include "mainwin.h"
#include "ui_mainwin.h"
// #include "uui_mainwin.h"

#include <GrapLineItem.h>
#include <GrapNodeItem.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QTimer>
#include<QDebug>
#include <common_func.hpp>

MainWin::MainWin(QWidget *parent) : QWidget(parent), ui(new Ui::mainwin) {
  ui->setupUi(this);
  tree = new TreeHead<Node<int>>();
  tree->create_tree();
  scene = new QGraphicsScene(this);
  grapPool = GrapItemManager::instance(scene);
  ball = new QGraphicsEllipseItem(0, 0, 60, 20);
  qDebug()<<"ball图层 "<<ball->zValue();
  ball->setZValue(2);
  scene->addItem(ball);
  //ball->hide();
  ui->view->setScene(scene); // QGraphicsView
  scene->update();

  ui->view->show();
  // connect(t, &QTimer::timeout, this, [this, nodet]() {
  //   //nodet->setPos(nodet->mapToScene(1, 1));
  //   // nodet->advance(10);
  // });
  connect(ui->btn_build, &QPushButton::clicked, this,
          &MainWin::btn_build_clicked);
  connect(ui->btn_reverse, &QPushButton::clicked, this,
          &MainWin::btn_reverse_clicked);
  connect(ui->btn_foreach, &QPushButton::clicked, this,
          &MainWin::animate_foreach);
}
MainWin::~MainWin() { delete ui; }

void MainWin::print_tree(NodePtr head) {
  qDebug() << "print_tree is called ";
  grapPool->hideAll();
  // 实际的节点个数
  //_SPC vector<NodePtr> a节点集合 = node_back_list(head);
  std::vector<NodePtr> a节点集合 = tree->foreach_back();
  for (auto ptr : a节点集合) {
    QString val = val_to_qstring(ptr->val);
    GrapNodeItem *curNodeItem = grapPool->getGrapNode(
        gridToCoordinate(ptr->row, ptr->col), val, ptr->color);
    // 连接父节点到子节点的线
    for (size_t j = 0; j < 2; ++j) {
      NodePtr child = nullptr;
      if (j == 0)
        child = ptr->left;
      else
        child = ptr->right;
      if (child != nullptr) {
        QTransform transform;
        auto point = gridToCoordinate(child->row, child->col);
        GrapNodeItem *end =
            qgraphicsitem_cast<GrapNodeItem *>(scene->itemAt(point, transform));
        GrapLineItem *curLineItem = grapPool->getGrapLine(curNodeItem, end);
        // 由于直线与2个图元连接，把直线添加到2个图元中
        curNodeItem->addLine(curLineItem);
        end->addLine(curLineItem);
      }
    }
  }
  scene->update();
}
QPointF MainWin::gridToCoordinate(int x, int y) {
  return QPointF(x * 40, y * 60);
}
void MainWin::btn_build_clicked() { print_tree(tree->head); }
void MainWin::btn_foreach_clicked() {
  qDebug() << "btn_foreach_clicked is called ";
  grapPool->hideAll();
}
void MainWin::btn_reverse_clicked() {
  this->tree->reverse_tree();
  this->print_tree(this->tree->head);
}
//https://www.codenong.com/cs111059714/
void MainWin::animate_foreach() {
  ball->show();
  scene->update();
  QTimeLine *timer = new QTimeLine(5000);
  timer->setFrameRange(0, 100);
  QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
  animation->setItem(ball);
  animation->setTimeLine(timer);
  auto xrr = tree->foreach_front();
  int sz = xrr.size();
  for (double i = 0; i < sz; ++i)
  {
    QPointF pos = gridToCoordinate(xrr[i]->row,xrr[i]->col);
    animation->setPosAt(i / sz, pos);
  }
  //scene->addItem(ball);
  timer->start();
  //ball->hide();
  scene->update();
  ui->view->show();
}
/*
  ball->show();
  QTimeLine *timer = new QTimeLine(5000);
  timer->setFrameRange(0, 100);
  QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
  animation->setItem(ball);
  animation->setTimeLine(timer);
  auto xrr = tree->foreach_ceng();
  int sz = xrr.size();
  for (double i = 0; i < sz; ++i)
  {
    QPointF pos = gridToCoordinate(xrr[i]->row,xrr[i]->col);
    animation->setPosAt(i / sz, pos);
  }
  //scene->addItem(ball);
  timer->start();
  ball->hide();

*/

/*
  ball->show();
  scene->update();
  QTimeLine timer(5000);
  timer.setFrameRange(0, 100);
  QGraphicsItemAnimation animation ;
  animation.setItem(ball);
  animation.setTimeLine(&timer);
  auto xrr = tree->foreach_ceng();
  int sz = xrr.size();
  for (double i = 0; i < sz; ++i)
  {
    QPointF pos = gridToCoordinate(xrr[i]->row,xrr[i]->col);
    animation.setPosAt(i / sz, pos);
  }
  //scene->addItem(ball);
  timer.start();
  ball->hide();
  scene->update();
*/