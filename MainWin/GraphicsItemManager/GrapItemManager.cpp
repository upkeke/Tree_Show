#include "GrapItemManager.h"
#include "GrapLineItem.h"
#include "GrapMoveItem.h"
#include "GrapNodeItem.h"
#include <BinaryTreeStr.hpp>
#include <FuncForHeadNode.h>
#include <QGraphicsScene>

using namespace sbt;
GrapItemManager::GrapItemManager(QGraphicsScene *scene)
    : grapNodePool(), curNodeindex(0), grapLinePool(), curLineIndex(0),
      scene(scene) {}

std::shared_ptr<GrapItemManager>
GrapItemManager::instance(QGraphicsScene *scene) {
  if (ItemManager == nullptr) {
    ItemManager = std::shared_ptr<GrapItemManager>(new GrapItemManager(scene));
  }
  return ItemManager;
}
GrapNodeItem *GrapItemManager::getGrapNode(NodePtr nodeptr, bool &isNew,
                                           QGraphicsItemGroup *grp) {
  auto temp = grapNodePool.size();
  GrapNodeItem *item = nullptr;
  if (curNodeindex == temp) {
    item = new GrapNodeItem(nodeptr);
    scene->addItem(item);
    grapNodePool.push_back(item);
    isNew = true;
  } else {
    item = grapNodePool[curNodeindex];
    item->reSet(nodeptr);
    isNew = false;
  }
  grp->addToGroup(item);
  nodeToGrapNode[nodeptr] = item;
  curNodeindex++;
  item->show();
  item->clearLines();
  return item;
}
void GrapItemManager::ShowDepthOrVal(bool flag) {
  for (int i = 0; i < curNodeindex; ++i) {
    grapNodePool[i]->SetIsShowDepth(flag);
  }
}
GrapNodeItem *GrapItemManager::whereGrapNode(NodePtr nodeptr) {
  if (nodeToGrapNode.contains(nodeptr)) {
    return nodeToGrapNode[nodeptr];
  }
  return nullptr;
}
std::pair<sbt::BinaryTreeStr *, QGraphicsItemGroup *>
GrapItemManager::treeWithItemGroup(sbt::BinaryTreeStr *tree,
                                   QGraphicsItemGroup *grp) {
  sbt::foreach_front(
      tree->get_head(),
      [](NodePtr cur, unordered_map<sbt::NodePtr, GrapNodeItem *> &mp,
         QGraphicsItemGroup *gp) {
        if (mp.contains(cur)) {
          gp->addToGroup(mp[cur]);
        }
      },
      this->nodeToGrapNode, grp);
  return {};
}
/**
 * @brief
 由于可能添加了子节点，添加子节点只能顺带修正col，不能修正row
 因此这儿需要修正row，同时添加偏移量
 *
 * @param head
 * @param offset
 */
void GrapItemManager::updateGrapNodePos(sbt::NodePtr head,
                                        const QPointF &offset) {

  int row = 0;
  sbt::foreach_mid(
      head,
      [](NodePtr cur, const QPointF &_offset,
         unordered_map<sbt::NodePtr, GrapNodeItem *> &_nodeToGrapNode,
         int &_row) {
        cur->row = _row++;
        cur->toScenePos(_offset);
        _nodeToGrapNode[cur]->setPos(cur->Pos());
      },
      offset, nodeToGrapNode, row);
}
void GrapItemManager::LineNodeToChild(GrapNodeItem * fatherItem) {
  auto fatherNode = fatherItem->getNodePtr();
  for (size_t j = 0; j < 2; ++j) {
    NodePtr childNode = nullptr;
    if (j == 0)
      childNode = fatherNode->left;
    else
      childNode = fatherNode->right;
    if (childNode != nullptr) {
      // 后序遍历，子节点图元必然先于父节点创建，可以不判断nodeToGrapNode[childNode]
      auto childItem = nodeToGrapNode[childNode];
      GrapLineItem *curLineItem = getGrapLine(fatherItem,childItem,j == 0);
    }
  }
}
GrapLineItem *GrapItemManager::getGrapLine(GrapNodeItem *front,
                                           GrapNodeItem *end) {

  auto temp = grapLinePool.size();
  GrapLineItem *item = nullptr;
  if (curLineIndex == temp) {
    item = new GrapLineItem(front, end);
    scene->addItem(item);
    grapLinePool.push_back(item);
  } else {
    item = grapLinePool[curLineIndex];
    item->setTwo(front, end);
  }
  curLineIndex++;
  item->show();
  // 由于直线与2个图元连接，把直线添加到2个图元中
  front->addLine(item);
  end->addLine(item);
  return item;
}
GrapLineItem *GrapItemManager::getGrapLine(GrapNodeItem *front,
                                           GrapNodeItem *end, bool isleft) {
  GrapLineItem *re = getGrapLine(front, end);
  re->setIsLeftLine(isleft);
  return re;
}
void GrapItemManager::hideSurplus() {
  for (size_t i = curNodeindex; i < grapNodePool.size(); ++i) {
    grapNodePool[i]->hide();
    nodeToGrapNode.erase(grapNodePool[i]->nodeptr);
  }
  for (size_t i = curLineIndex; i < grapLinePool.size(); ++i) {
    grapLinePool[i]->hide();
  }
  scene->update();
}

void GrapItemManager::hideNodes(NodePtr head) {
  sbt::foreach_front(
      head,
      [](NodePtr cur,
         unordered_map<sbt::NodePtr, GrapNodeItem *> &_nodeToGrapNode) {
        _nodeToGrapNode[cur]->hide();
        _nodeToGrapNode[cur]->reMoveLines();
        _nodeToGrapNode.erase(cur);
      },
      nodeToGrapNode);
  scene->update();
}

GrapMoveItem *GrapItemManager::getGrapMove(const QPointF &pos) {
  auto temp = grapMovePool.size();
  GrapMoveItem *item = nullptr;
  if (curLineIndex == temp) {
    item = new GrapMoveItem(pos);
    scene->addItem(item);
    grapMovePool.push_back(item);
  } else {
    item = grapMovePool[curMoveIndex];
  }
  curMoveIndex++;
  item->show();
  return item;
}
GrapItemManager::~GrapItemManager() {}
