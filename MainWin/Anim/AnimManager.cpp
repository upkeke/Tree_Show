#include "AnimManager.h"
#include <GrapItemManager.h>
#include <GrapMoveItem.h>
#include <GrapNodeItem.h>
#include <GrapUi.h>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

qreal disBtwItem(const QPointF &p1, const QPointF &p2) {
  auto p = p1 - p2;
  return std::sqrt(p.rx() * p.rx() + p.y() * p.y());
}
AnimManager::AnimManager(GrapMoveItem *_五角星图元,
                         const std::array<UiForeachBtn *, 4> &_遍历列表图元,
                         QObject *parent)
    : QObject(parent) {
  this->_五角星图元 = _五角星图元;
  _五角星动画组 = new QParallelAnimationGroup();
  QPropertyAnimation *am1 = new QPropertyAnimation(_五角星图元, "pos");
  QPropertyAnimation *am2 = new QPropertyAnimation(_五角星图元, "rotation");
  _五角星动画组->addAnimation(am1);
  _五角星动画组->addAnimation(am2);
  auto scene = this->_五角星图元->scene();
  connect(am1, &QPropertyAnimation::valueChanged,
          [scene](const QVariant &value) { scene->update(); });
  connect(am2, &QPropertyAnimation::valueChanged,
          [scene](const QVariant &value) { scene->update(); });

  this->_遍历列表图元 = _遍历列表图元;
  _遍历列表展开动画组 = new QParallelAnimationGroup();
  int delay = 0;
  for (auto ptr : _遍历列表图元) {
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
AnimManager::instance(GrapMoveItem *_五角星图元,
                      const std::array<UiForeachBtn *, 4> &_遍历列表图元) {
  if (manager == nullptr) {
    manager = std::shared_ptr<AnimManager>(
        new AnimManager(_五角星图元, _遍历列表图元));
  }

  return manager;
}
void AnimManager::_列表展开动画(QPointF startPos) {
  auto rec = _遍历列表图元[0]->boundingRect();
  QPointF endPos(-rec.width(), 0);
  auto dy1 = rec.height();
  endPos += startPos;
  for (auto x : _遍历列表图元)
    x->show();
  _遍历列表图元[0]->scene()->update();
  for (int i = 0; i < _遍历列表图元.size(); ++i) {
    QSequentialAnimationGroup *sqanim =
        static_cast<QSequentialAnimationGroup *>(
            _遍历列表展开动画组->animationAt(i));
    QPropertyAnimation *panim =
        static_cast<QPropertyAnimation *>(sqanim->animationAt(1));
    disconnect(panim, &QPropertyAnimation::finished, _遍历列表图元[i],
               &UiForeachBtn::hide_);
    panim->setStartValue(startPos);
    panim->setEndValue(endPos);
    startPos.setY(startPos.ry() + dy1);
    endPos.setY(endPos.ry() + dy1);
  }
  _遍历列表展开动画组->start();
}
void AnimManager::_列表收起动画(QPointF startPos) {
  auto rec = _遍历列表图元[0]->boundingRect();
  QPointF endPos(-rec.width(), 0);
  auto dy1 = rec.height();
  endPos += startPos;
  // for (auto x : _遍历列表图元)
  //   x->hide();
  for (int i = 0; i < _遍历列表图元.size(); ++i) {
    QSequentialAnimationGroup *sqanim =
        static_cast<QSequentialAnimationGroup *>(
            _遍历列表展开动画组->animationAt(i));
    QPropertyAnimation *panim =
        static_cast<QPropertyAnimation *>(sqanim->animationAt(1));
    connect(panim, &QPropertyAnimation::finished, _遍历列表图元[i],
            &UiForeachBtn::hide_);
    panim->setStartValue(startPos);
    panim->setEndValue(endPos);
    startPos.setY(startPos.ry() + dy1);
    endPos.setY(endPos.ry() + dy1);
  }
  // for (auto x : _遍历列表图元)
  //   x->show();
  _遍历列表展开动画组->start();
}
void AnimManager::_遍历列表展开收起动画(QObject *root) {
  UiForeachRootBtn *rroot = static_cast<UiForeachRootBtn *>(root);
  QPointF startPos = rroot->boundingRect().bottomRight();
  startPos = rroot->mapToScene(startPos);
  bool flag = !rroot->IsOpen();
  if (flag)
    _列表展开动画(startPos);
  else {
    auto rec = _遍历列表图元[0]->boundingRect();
    startPos = startPos + QPointF(-rec.width(), 0);
    _列表收起动画(startPos);
  }
  rroot->set_IsOpen(flag);
}

void AnimManager::_五角星遍历动画(_SPC vector<sbt::NodePtr> nodeptr_list,
                                  std::shared_ptr<GrapItemManager> grapPool) {
  QPropertyAnimation *am1 =
      static_cast<QPropertyAnimation *>(_五角星动画组->animationAt(0));
  QPropertyAnimation *am2 =
      static_cast<QPropertyAnimation *>(_五角星动画组->animationAt(1));
  am1->setDuration(10000);
  am1->setStartValue(QPointF{-30, -30});
  am1->setEndValue(QPointF{-30, -30});
  am2->setDuration(10000);
  am2->setStartValue(0);
  am2->setEndValue(1800);
  int sz = nodeptr_list.size();
  for (double i = 1; i <= sz; ++i) {
    am1->setKeyValueAt(i / (sz + 1), nodeptr_list[i - 1]->Pos());
  }
  // 节点的动画
  connect(
      am1, &QPropertyAnimation::valueChanged, this,
      [nodeptr_list, grapPool, curIndex = 0](const QVariant &value) mutable {
        if (curIndex < nodeptr_list.size()) {
          qreal dis =
              disBtwItem(nodeptr_list[curIndex]->Pos(), value.toPointF());
          if (dis < 20) {
            nodeptr_list[curIndex]->setColor(sbt::NodeColor::green);
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
        } else {
          curIndex = 0;
        }
      });

  _五角星动画组->start();
}
AnimManager::~AnimManager() {}