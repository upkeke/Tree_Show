#include "widget.h"
#include "Anim/AnimManager.h"
#include <GrapUi.h>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QVBoxLayout>

testWin ::testWin(QWidget *parent) : QWidget(parent) {
  auto layout = new QVBoxLayout(this);
  auto btn = new QPushButton("test", this);
  auto view = new QGraphicsView(this);
  scene = new QGraphicsScene(this);
  // QLineF l1(QPointF{100, 100}, QPointF{600, 600});
  // auto lin = new QGraphicsLineItem(l1);
  // scene->addItem(lin);
  view->setScene(scene);
  view->show();
  layout->addWidget(btn);
  layout->addWidget(view);
  this->setLayout(layout);

  // auto ma = AnimManager::instance();
  // auto grt = ma->creat_foreach_am(QPointF{10, 10}, ls, scene);
  connect(btn, &QPushButton::clicked, this, &testWin::test2);
  // for (int i = 0; i < 4; ++i) {
  //   auto m1 = static_cast<QPropertyAnimation *>(grt->animationAt(i));
  //   connect(m1, &QPropertyAnimation::valueChanged, scene,
  //           [scene](const QVariant &value) { scene->update(); });
  // }
}
void testWin::test1() {
  QParallelAnimationGroup *move_group = new QParallelAnimationGroup();
  QList<UiForeachBtn *> arr(4);
  arr[0] = new UiForeachBtn(EachOrder::先序);
  arr[1] = new UiForeachBtn(EachOrder::中序);
  arr[2] = new UiForeachBtn(EachOrder::后序);
  arr[3] = new UiForeachBtn(EachOrder::层级);
  auto pos1 = QPointF{100, 100};
  auto dy1 = arr[0]->boundingRect().height();
  auto pos2 = pos1;
  for (auto i : arr) {
    i->setPos(pos2);
    scene->addItem(i);
    pos2.setY(pos2.ry() + dy1);
  }
  scene->update();
  QPointF endpos(-arr[0]->boundingRect().width(), 0);
  endpos += pos1;
  int delay = 0;

  for (auto btn : arr) {
    qDebug() << "pos1 " << pos1 << " endpos " << endpos;
    QTimer::singleShot(
        delay, [move_group, delay, pos1, dy1, endpos, this, btn] {
          QPropertyAnimation *am1 = new QPropertyAnimation(btn, "pos");
          am1->setDuration(10000);
          am1->setStartValue(pos1);
          am1->setEndValue(endpos);
          am1->setEasingCurve(QEasingCurve::InOutCirc);
          qDebug() << "延时函数调用";
          // connect(am1, &QPropertyAnimation::valueChanged, this,
          //         [this](const QVariant &value) {
          //           qDebug() << "QPropertyAnimation 函数调用";

          //           scene->update();
          //         });

          move_group->addAnimation(am1);
        });
    pos1.setY(pos1.ry() + dy1);
    endpos.setY(endpos.ry() + dy1);
    delay += 1000;
  }
  QTimer::singleShot(1, [move_group]() { move_group->start(); });
  // move_group->start(); //不能直接启动，可以能上面的动画还没有创建好
}

void testWin::test2() {
  QParallelAnimationGroup *move_group = new QParallelAnimationGroup();
  QList<UiForeachBtn *> arr(4);
  arr[0] = new UiForeachBtn(EachOrder::先序);
  arr[1] = new UiForeachBtn(EachOrder::中序);
  arr[2] = new UiForeachBtn(EachOrder::后序);
  arr[3] = new UiForeachBtn(EachOrder::层级);
  auto pos1 = QPointF{100, 100};
  auto dy1 = arr[0]->boundingRect().height();
  auto pos2 = pos1;
  for (auto i : arr) {
    i->setPos(pos2);
    scene->addItem(i);
    pos2.setY(pos2.ry() + dy1);
  }
  scene->update();
  QPointF endpos(-arr[0]->boundingRect().width(), 0);
  endpos += pos1;
  int delay = 0;
  for (auto ptr : arr) {
    QSequentialAnimationGroup *ag1 = new QSequentialAnimationGroup();
    ag1->addPause(delay);
    QPropertyAnimation *am1 = new QPropertyAnimation(ptr, "pos");
    am1->setDuration(10000);
    am1->setStartValue(pos1);
    am1->setEndValue(endpos);
    ag1->addAnimation(am1);

    pos1.setY(pos1.ry() + dy1);
    endpos.setY(endpos.ry() + dy1);
    delay += 1000;
    move_group->addAnimation(ag1);
  }

  move_group->start();
}

//QParallelAnimationGroup中嵌套QSequentialAnimationGroup，QSequentialAnimationGroup插入动画之前先设置一些延时