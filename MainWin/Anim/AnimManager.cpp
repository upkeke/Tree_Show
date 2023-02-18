#include "AnimManager.h"
#include <GrapItemManager.h>
// #include <GrapMoveItem.h>
#include "GrapAnimItem.h"
#include <GrapNodeItem.h>
#include <HeadNode.h>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

namespace {
_SPC vector<sbt::NodePtr> getListByOrder(EechOrder order,
                                         sbt::NodePtr curtree) {
  switch (order) {
  case EechOrder::先序:
    return foreach_front_v(curtree);
  case EechOrder::中序:
    return foreach_mid_v(curtree);
  case EechOrder::后序:
    return foreach_back_v(curtree);
  case EechOrder::层级:
    return foreach_ceng_v(curtree);
  case EechOrder::选择:
    break;
  }
  return {};
}
} // namespace
qreal disBtwItem(const QPointF &p1, const QPointF &p2) {
  auto p = p1 - p2;
  return std::sqrt(p.rx() * p.rx() + p.y() * p.y());
}
AnimManager::AnimManager(std::shared_ptr<GrapItemManager> _grapPool) {
  // this->_五角星图元 = _五角星图元;
  this->grapPool = _grapPool;
  init_grap();
  init_anim();
}
void AnimManager::init_grap() {

  _五角星图元 = new GrapMoveItem(QPointF{40, 40});
  auto scene = grapPool->getScene();
  scene->addItem(_五角星图元);
  _五角星图元->hide();

  _rootBtn = new UiForeachRootBtn();
  _rootBtn->setPos(-300, 0);
  childBtnList[0] = new UiForeachBtn(EechOrder::先序);
  childBtnList[1] = new UiForeachBtn(EechOrder::中序);
  childBtnList[2] = new UiForeachBtn(EechOrder::后序);
  childBtnList[3] = new UiForeachBtn(EechOrder::层级);
  for (auto i : childBtnList) {
    scene->addItem(i);
    i->hide();
  }
  // 由scene释放内存
  scene->addItem(_rootBtn);

  connect(_rootBtn, &UiForeachRootBtn::RootBtnPress, this,
          &AnimManager::_遍历列表展开收起动画);
  // 点击遍历按钮，五角星开始遍历动画
  for (auto ptr : childBtnList) {
    connect(ptr, &UiForeachBtn::ChildBtnPress, this, [this](EechOrder order) {
      this->_遍历列表展开收起动画();
      _rootBtn->set_order(order);
      this->_五角星遍历动画(order);
    });
  }
}
void AnimManager::init_anim() {
  _五角星动画组 = new QParallelAnimationGroup();
  QPropertyAnimation *am1 = new QPropertyAnimation(_五角星图元, "pos");
  QPropertyAnimation *am2 = new QPropertyAnimation(_五角星图元, "rotation");
  _五角星动画组->addAnimation(am1);
  _五角星动画组->addAnimation(am2);
  auto scene = this->_五角星图元->scene();
  connect(am1, &QPropertyAnimation::valueChanged,
          [this, scene](const QVariant &value) {
            // 结束
            if (curIndex >= nodeptr_list.size()) {
              this->_五角星图元->hide();
              curIndex = 0;
              for (auto x : nodeptr_list) {
                x->color = sbt::NodeColor::yellow;
              }
              (*p_head)->color = sbt::NodeColor::magenta;
              return;
            }
            qreal dis =
                disBtwItem(nodeptr_list[curIndex]->Pos(), value.toPointF());
            if (dis < 20) {
              nodeptr_list[curIndex]->color = sbt::NodeColor::green;
              // 当五角星靠近图元节点的时候放大节点图元，然后复原
              QPropertyAnimation *tpanm = new QPropertyAnimation(
                  grapPool->whereGrapNode(nodeptr_list[curIndex]), "scale");
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
            scene->update();
          });
  connect(am2, &QPropertyAnimation::valueChanged,
          [scene](const QVariant &value) { scene->update(); });

  _遍历列表展开动画组 = new QParallelAnimationGroup();
  int delay = 0;
  for (auto ptr : childBtnList) {
    // connect(ptr,)
    QSequentialAnimationGroup *ag1 = new QSequentialAnimationGroup();
    ag1->addPause(delay); // 插入延时
    QPropertyAnimation *am1 = new QPropertyAnimation(ptr, "pos");
    // 方便
    // 函数》》_遍历列表展开收起动画《《断开，因为那边一开始只能断开，但是没有连接过，就直接断开不合适
    connect(am1, &QPropertyAnimation::finished, ptr, &UiForeachBtn::hide_);
    am1->setDuration(1000);
    am1->setEasingCurve(QEasingCurve::OutCurve);
    ag1->addAnimation(am1);
    delay += 300;
    _遍历列表展开动画组->addAnimation(ag1);
  }
}
std::shared_ptr<AnimManager>
AnimManager::instance(std::shared_ptr<GrapItemManager> _grapPool) {
  if (manager == nullptr) {
    manager = std::shared_ptr<AnimManager>(new AnimManager(_grapPool));
  }
  return manager;
}
void AnimManager::setHeadNode(sbt::NodePtr *head) { this->p_head = head; }
void AnimManager::_列表展开动画(QPointF startPos) {
  auto rec = childBtnList[0]->boundingRect();
  QPointF endPos(-rec.width(), 0);
  auto dy1 = rec.height();
  endPos += startPos;
  for (auto x : childBtnList)
    x->show();
  childBtnList[0]->scene()->update();
  for (int i = 0; i < childBtnList.size(); ++i) {
    QSequentialAnimationGroup *sqanim =
        static_cast<QSequentialAnimationGroup *>(
            _遍历列表展开动画组->animationAt(i));
    QPropertyAnimation *panim =
        static_cast<QPropertyAnimation *>(sqanim->animationAt(1));
    disconnect(panim, &QPropertyAnimation::finished, childBtnList[i],
               &UiForeachBtn::hide_);
    panim->setStartValue(startPos);
    panim->setEndValue(endPos);
    startPos.setY(startPos.ry() + dy1);
    endPos.setY(endPos.ry() + dy1);
  }
  _遍历列表展开动画组->start();
}
void AnimManager::_列表收起动画(QPointF startPos) {
  auto rec = childBtnList[0]->boundingRect();
  QPointF endPos(-rec.width(), 0);
  auto dy1 = rec.height();
  endPos += startPos;
  // for (auto x : childBtnList)
  //   x->hide();
  for (int i = 0; i < childBtnList.size(); ++i) {
    QSequentialAnimationGroup *sqanim =
        static_cast<QSequentialAnimationGroup *>(
            _遍历列表展开动画组->animationAt(i));
    QPropertyAnimation *panim =
        static_cast<QPropertyAnimation *>(sqanim->animationAt(1));
    connect(panim, &QPropertyAnimation::finished, childBtnList[i],
            &UiForeachBtn::hide_);
    panim->setStartValue(startPos);
    panim->setEndValue(endPos);
    startPos.setY(startPos.ry() + dy1);
    endPos.setY(endPos.ry() + dy1);
  }
  // for (auto x : childBtnList)
  //   x->show();
  _遍历列表展开动画组->start();
}
void AnimManager::_遍历列表展开收起动画() {
  UiForeachRootBtn *rroot = this->_rootBtn;
  QPointF startPos = rroot->boundingRect().bottomRight();
  startPos = rroot->mapToScene(startPos);
  bool flag = !rroot->IsOpen();
  if (flag)
    _列表展开动画(startPos);
  else {
    auto rec = childBtnList[0]->boundingRect();
    startPos = startPos + QPointF(-rec.width(), 0);
    _列表收起动画(startPos);
  }
  rroot->set_IsOpen(flag);
}

void AnimManager::_五角星遍历动画(EechOrder order) {

  _五角星图元->show();
  nodeptr_list = ::getListByOrder(order, *p_head);
  this->curIndex = 0;
  QPropertyAnimation *am1 =
      static_cast<QPropertyAnimation *>(_五角星动画组->animationAt(0));
  QPropertyAnimation *am2 =
      static_cast<QPropertyAnimation *>(_五角星动画组->animationAt(1));
  auto xx = am1->keyValues();
  am1->setDuration(10000);
  am1->setStartValue(QPointF{-30, -30});
  int sz = nodeptr_list.size();
  QList<KeyValue> ls;
  for (double i = 1; i <= sz; ++i) {
    ls.push_back({i / (sz + 1), nodeptr_list[i - 1]->Pos()});
    // 这个不会替换之前的值，只会插值
    //  am1->setKeyValueAt(i / (sz + 1), nodeptr_list[i -1]->Pos());
  }
  am1->setKeyValues(ls);
  am1->setEndValue(QPointF{-30, -30});
  am2->setDuration(10000);
  am2->setStartValue(0);
  am2->setEndValue(1800);

  _五角星动画组->start();
}
AnimManager::~AnimManager() {}