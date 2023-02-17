#include "GrapUiManager.h"
#include <QGraphicsScene>
#include <QResource>
GrapUiManager::GrapUiManager(QGraphicsScene *scene) {
  
  _rootBtn = new UiForeachRootBtn();
  _rootBtn->setPos(-300, 0);
  childBtnList[0] = new UiForeachBtn(EechOrder::先序);
  childBtnList[1] = new UiForeachBtn(EechOrder::中序);
  childBtnList[2] = new UiForeachBtn(EechOrder::后序);
  childBtnList[3] = new UiForeachBtn(EechOrder::层级);
  this->scene = scene;
  for (auto i : childBtnList) {
    scene->addItem(i);
    i->hide();
  }
  // 由scene释放内存
  scene->addItem(_rootBtn);
}

std::shared_ptr<GrapUiManager> GrapUiManager::instance(QGraphicsScene *scene) {
  if (manager == nullptr) {
    manager = std::shared_ptr<GrapUiManager>(new GrapUiManager(scene));
  }
  return manager;
}

GrapUiManager::~GrapUiManager() {}
UiForeachRootBtn *GrapUiManager::RootBtn() const { return _rootBtn; }
const std::array<UiForeachBtn *, 4> &GrapUiManager::ChildBtn() const {
  return childBtnList;
}
