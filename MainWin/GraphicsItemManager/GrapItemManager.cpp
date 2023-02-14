#include "GrapItemManager.h"
#include "GrapLineItem.h"
#include "GrapMoveItem.h"
#include "GrapNodeItem.h"
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
GrapNodeItem *GrapItemManager::getGrapNode(NodePtr nodeptr, bool &isNew) {
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
void GrapItemManager::updateGrapNodePos(sbt::NodePtr head,
                                        const QPointF &offset) {
  sbt::foreach_front(
      head,
      [](NodePtr cur, const QPointF &_offset,
         unordered_map<sbt::NodePtr, GrapNodeItem *> &_nodeToGrapNode) {
        cur->offsetPos(_offset);
        _nodeToGrapNode[cur]->setPos(cur->Pos());
      },
      offset, nodeToGrapNode);
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

void GrapItemManager::hideSurplus() {
  for (size_t i = curNodeindex; i < grapNodePool.size(); ++i) {
    grapNodePool[i]->hide();
    nodeToGrapNode.erase(grapNodePool[i]->nodeptr);
  }
  for (size_t i = curLineIndex; i < grapLinePool.size(); ++i) {
    grapLinePool[i]->hide();
  }
  // curNodeindex = 0;
  // curLineIndex = 0;
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
  // for (auto i : nodes) {
  //   nodeToGrapNode[i]->hide();
  //   nodeToGrapNode[i]->reMoveLines();
  //   nodeToGrapNode.erase(i);
  // }

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
