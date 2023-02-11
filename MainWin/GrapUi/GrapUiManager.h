
#pragma once
#ifndef __GRAPUIMANAGER__
#define __GRAPUIMANAGER__

#include "GrapUi.h"
#include "GrapUi_Bin.h"
#include <array>
class QGraphicsScene;
class GRAPUI_LIB_EXPORT GrapUiManager {
public:
  static std::shared_ptr<GrapUiManager> instance(QGraphicsScene *scene);
  UiForeachRootBtn *RootBtn() const;
  const std::array<UiForeachBtn *, 4> &ChildBtn() const;
  ~GrapUiManager();



private:
  GrapUiManager(QGraphicsScene *scene);

  inline static std::shared_ptr<GrapUiManager> manager = nullptr;
  QGraphicsScene *scene = nullptr;

  // 下拉框的根
  UiForeachRootBtn *_rootBtn = nullptr;
  // 下拉框的4个子框
  std::array<UiForeachBtn *, 4> childBtnList{};
};

#endif