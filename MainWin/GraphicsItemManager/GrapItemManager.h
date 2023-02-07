#pragma once
#ifndef __GRAPITEMMANAGER__
#define __GRAPITEMMANAGER__
#include <BinaryTree.hpp>
#include <config.h>
#include <memory>
#include <unordered_map>
using std::unordered_map;
class GrapNodeItem;
class GrapLineItem;
class QGraphicsScene;
class GrapMoveItem;

/**
 * @brief 这个是一个图元观测器
 不负责GrapLineItem和GrapNodeItem GrapMoveItem的释放
GrapNodeItem也不会负责NodePtr的释放
 *
 */
class GrapItemManager {
public:
  static std::shared_ptr<GrapItemManager> instance(QGraphicsScene *scene);
  /**
   * @brief 获得一个节点图元
   节点图元池如果还有多余的节点图元，将它节点设置nodepter，直接返回，
   如果没有，通过传入的节点指针构造一个节点图元
   *
   * @param nodeptr
   * @return GrapNodeItem* 获得的节点图元
   */
  GrapNodeItem *getGrapNode(NodePtr nodeptr);
  /**
   * @brief 获得包含nodeptr节点的图元
   有些情况需要通过节点直到包含它的图元指针
   *
   * @param nodeptr 图元的节点指针
   * @return GrapNodeItem* 包含节点指针的图元
   */
  GrapNodeItem *whereGrapNode(NodePtr nodeptr);
  /**
   * @brief G构造一个直线图元，用于连接2个树节点
   如果还有剩余，设置一些它的2个断点，直接返回
   如果没有就构造一个
   *
   * @param front 直线的一端的树节点
   * @param end 直线的一端的树节点
   * @return GrapLineItem* 直线图元的地址
   */
  GrapLineItem *getGrapLine(GrapNodeItem *front, GrapNodeItem *end);
  /**
   * @brief 一个运动图元
   遍历每个树节点的时候需要一个图元根据遍历顺序不段的移动
   这个函数并没有用过，可以忽略
   * 
   * @param pos 图元生成的位置，在场景中坐标
   * @return GrapMoveItem* 
   */
  GrapMoveItem *getGrapMove(const QPointF &pos);
  /**
   * @brief 隐藏多余的图元
   * 
   */
  void hideSurplus(); 
  /**
   * @brief 隐藏所有的图元
   * 
   */
  void hideAll();    

  ~GrapItemManager();

private:
  inline static std::shared_ptr<GrapItemManager> ItemManager = nullptr;
  QGraphicsScene *scene = nullptr;
  GrapItemManager(QGraphicsScene *scene);
  ///  @brief 节点图元池
  _SPC vector<GrapNodeItem *> grapNodePool;
  ///  @brief 节点池的前curNodeindex被使用
  size_t curNodeindex = 0;
  /**
   * @brief 通过节点指针找到节点图元
   有2种方案，
   一种是在NodePtr中加一个GrapNodeItem
   *成员变量,会增加NodePtr和GrapNodeItem的耦合 一种是在这儿设置一个哈希表，
   它会有一个小bug， 如果NodePtr不在curNodeindex
   前面的元素里面，但存在于哈希表中，同样能找到它之前的
   GrapNodeItem，这样会产生混乱 只要外部禁止构造GrapNodeItem对象就不会出现
   *
   */
  unordered_map<NodePtr, GrapNodeItem *> nodeToGrapNode;
  _SPC vector<GrapLineItem *> grapLinePool;
  size_t curLineIndex = 0;
  _SPC vector<GrapMoveItem *> grapMovePool;
  size_t curMoveIndex = 0;
};

#endif