#include "GrapItemManager.h"
#include "GrapLineItem.h"
#include "GrapNodeItem.h"
#include <BinaryTree.hpp>
#include <QGraphicsScene>

// #include <container.h>

GrapItemManager::GrapItemManager(QGraphicsScene *scene)
    : grapNodePool(), curNodeindex(0), grapLinePool(), curLineIndex(0),
      scene(scene) {}

std::shared_ptr<GrapItemManager>
GrapItemManager::instance(QGraphicsScene *scene) {
  if (ItemManager == nullptr) {
    // ItemManager = std::make_shared<GrapItemManager>();
    ItemManager = std::shared_ptr<GrapItemManager>(new GrapItemManager(scene));
  }

  return ItemManager;
}
GrapNodeItem *GrapItemManager::getGrapNode(NodePtr nodeptr) {
  auto temp = grapNodePool.size();
  GrapNodeItem *item = nullptr;
  if (curNodeindex == temp) {
    item = new GrapNodeItem(nodeptr);
    scene->addItem(item);
    grapNodePool.push_back(item);
  } else {
    item = grapNodePool[curNodeindex];
    item->reSet(nodeptr);
  }
  curNodeindex++;
  item->show();
  item->clearLines();
  return item;
}

size_t GrapItemManager::grapNodeSize() { return grapNodePool.size(); }
size_t GrapItemManager::grapIndexSize() { return grapLinePool.size(); }

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
  return item;
}

void GrapItemManager::hideSurplus() {
  for (size_t i = curNodeindex; i < grapNodePool.size(); ++i) {
    grapNodePool[i]->hide();
  }
  for (size_t i = curLineIndex; i < grapLinePool.size(); ++i) {
    grapLinePool[i]->hide();
  }
  curNodeindex = 0;
  curLineIndex = 0;
  scene->update();
}

void GrapItemManager::hideAll() {
  for (auto i : grapNodePool) {
    i->hide();
  }
  for (auto i : grapLinePool) {
    i->hide();
  }
  scene->update();
}

GrapItemManager::~GrapItemManager() {}
