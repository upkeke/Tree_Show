// author : keke
// date : 2023/02/10
#pragma once
#ifndef __ANIMMANAGER__
#define __ANIMMANAGER__

#include "Anim_Bin1.h"
#include <NodeStr.hpp>
#include <QList>
#include <QObject>
#include <QPointF>
#include <array>
#include <memory>
#include <vector>

// inline qreal disBtwItem(const QPointF &p1, const QPointF &p2) {
//   auto p = p1 - p2;
//   return std::sqrt(p.rx() * p.rx() + p.y() * p.y());
// }
class QParallelAnimationGroup;
class QPropertyAnimation;
class UiForeachBtn;
class QGraphicsScene;
class GrapMoveItem;
class GrapItemManager;
class UiForeachRootBtn;
class ANIM_LIB_EXPORT_XX AnimManager : public QObject {
  // Q_OBJECT
public:
  static std::shared_ptr<AnimManager>
  instance(GrapMoveItem *_五角星图元,
           const std::array<UiForeachBtn *, 4> &_遍历列表图元);
  void _列表展开动画(QPointF startPos);
  void _列表收起动画(QPointF startPos);
  /**
   * @brief

   第一个参数 pos是下拉框的生成位置，它是基准点
   第二个参数 flag  true 为展开， false为收起
   方便后面复用
   *
   */
  void _遍历列表展开收起动画(QObject *root);

  /**
   * @brief 这个函数是获得五角的动画组

   第一个参数是五角星图元
   第二个参数是 五角星要遍历的节点图元
   第三个参数
   图元管理器，这而设计可能有点问题，我需要通过树节点找它的节点图元，我把这个函数放在图元管理器实现的，并不能通过树节点找到它对应的图元

   函数作用说明，根据传入的nodeptr_list，包含每个节点的坐标，它们连成一条线，这就是五角星的运动轨迹
   还有一个效果，就是五角星访问到节点图元的时候，节点图元会放大1.5倍，然后缩小
   *
   */
  void _五角星遍历动画(_SPC vector<sbt::NodePtr> nodeptr_list,
                       std::shared_ptr<GrapItemManager> grapPool);
  ~AnimManager();

private:
  AnimManager(GrapMoveItem *_五角星图元,
              const std::array<UiForeachBtn *, 4> &_遍历列表图元,
              QObject *parent = nullptr);

  inline static std::shared_ptr<AnimManager> manager = nullptr;
  /**
   * @brief 五角星，遍历的运动单位，根据遍历顺序依次访问每个节点图元
   *
   */
  QParallelAnimationGroup *_五角星动画组 = nullptr;
  GrapMoveItem *_五角星图元;
  /**
   * @brief 当要切换遍历方式的时候，会出现下拉菜单，每一个遍历框会依序滑进来
   *
   */
  QParallelAnimationGroup *_遍历列表展开动画组 = nullptr;
  std::array<UiForeachBtn *, 4> _遍历列表图元{};
};

#endif