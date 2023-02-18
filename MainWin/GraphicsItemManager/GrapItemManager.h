#pragma once
#ifndef __GRAPITEMMANAGER__
#define __GRAPITEMMANAGER__
#include "Grap_Bin.h"
#include <QObject>

#include <QStrNode.hpp>
#include <config.h>
#include <memory>
#include <unordered_map>
// #include<BinaryTreeStr.hpp>

using std::unordered_map;
class GrapNodeItem;
class GrapLineItem;
class QGraphicsScene;
class GrapMoveItem;
class QGraphicsItemGroup;
namespace sbt {
class BinaryTreeStr;

}
/**
 * @brief 这个是一个图元观测器
 不负责GrapLineItem和GrapNodeItem GrapMoveItem的释放
GrapNodeItem也不会负责NodePtr的释放
 *
 */
class GRAP_LIB_EXPORT GrapItemManager : public QObject {
  Q_OBJECT
public:
  static std::shared_ptr<GrapItemManager> instance(QGraphicsScene *scene);
  QGraphicsScene *getScene();
  /**
   * @brief 获得一个节点图元
   节点图元池如果还有多余的节点图元，将它节点设置nodepter，直接返回，
   如果没有，通过传入的节点指针构造一个节点图元
   *
   * @param nodeptr
   * @return GrapNodeItem* 获得的节点图元
   */
  GrapNodeItem *getGrapNode(sbt::NodePtr nodeptr, bool &isNew,
                            sbt::NodePtr headptr);
  void deleteTree(GrapNodeItem *);
  /**
   * @brief  显示或者显示深度
   *
   * @param flag true 显示深度，false显示val
   */
  void mergeTree(GrapNodeItem *main_item, GrapNodeItem *sub_item);
  void ShowDepthOrVal(bool flag);
  /**
   * @brief 获得包含nodeptr节点的图元
   有些情况需要通过节点直到包含它的图元指针
   *
   * @param nodeptr 图元的节点指针
   * @return GrapNodeItem* 包含节点指针的图元
   */
  GrapNodeItem *whereGrapNode(sbt::NodePtr nodeptr);
  /**
   * @brief 为头节点图元的每一个子节点图元设置根节点
   *
   * @param headItem
   */
  void reSetTreeNodeItemHead(GrapNodeItem *treeNodeItem, sbt::NodePtr headPtr);

  /**
   * @brief 图元根据节点位置归位
   *
   */
  void updateGrapNodePos(sbt::NodePtr head);
  /**
   * @brief father 和 child的位置禁止传反
   *
   * @param father 直线的一端的树节点
   * @param child 直线的一端的树节点
   * @return GrapLineItem* 直线图元的地址
   */
  GrapLineItem *getGrapLine(GrapNodeItem *father, GrapNodeItem *child,
                            bool isleft);
  void removeLine(GrapLineItem *line);
  /**
   * @brief 断开father和child
   隐藏二者之间的直线
   去掉father内包含的line
   将
   *
   * @param father
   * @param child
   */
  void disconnectGrapNode(GrapNodeItem *father, GrapNodeItem *child);
  /**
   * @brief 生成连接子节点的直线
   *
   * @param father
   */
  void LineNodeToChild(GrapNodeItem *fatherItem);

  /**
   * @brief 隐藏多余的图元
   *
   */
  // void hideSurplus();
  /**
   * @brief 隐藏所有的图元
   *
   */
  // void hideNodes(sbt::NodePtr head);

  ~GrapItemManager();

private:
  inline static std::shared_ptr<GrapItemManager> ItemManager = nullptr;
  QGraphicsScene *scene = nullptr;
  GrapItemManager(QGraphicsScene *scene);
  // 空闲的节点图元，这个freeNodePool里面GrapNodeItem含有Node
  _SPC stack<GrapNodeItem *> freeNodePool;

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
  unordered_map<sbt::NodePtr, GrapNodeItem *> nodeToGrapNode;
  _SPC stack<GrapLineItem *> freeLinePool;
};

#endif