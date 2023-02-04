// author : keke
// date : 2023/01/31
#pragma once
#ifndef __GRAPHITEMMANAGER__
#define __GRAPHITEMMANAGER__
#include <config.h>
#include <memory>
#include <QPointF>
class GrapNodeItem;
class GrapLineItem;
class QGraphicsScene;
//class QPointF;
class QString;
#ifndef NODECOLOR
#define NODECOLOR
enum class NodeColor {
  yellow,
  green,
  pink,
  black,
};
#endif

class GrapItemManager {
public:
  static std::shared_ptr<GrapItemManager> instance(QGraphicsScene *scene);
  GrapNodeItem *getGrapNode(const QPointF &pos, const QString& val, NodeColor pix_c);
  size_t grapNodeSize();
  size_t grapIndexSize();

  GrapLineItem *getGrapLine(GrapNodeItem *front, GrapNodeItem *end);
  void hideSurplus(); //隐藏多余的图元
  void hideAll();
  ~GrapItemManager();

private:
  inline static std::shared_ptr<GrapItemManager> ItemManager = nullptr;
  QGraphicsScene *scene = nullptr;
  GrapItemManager(QGraphicsScene *scene);
  _SPC vector<GrapNodeItem *> grapNodePool;
  //con::vector<GrapNodeItem *>::Iter curNodeIter;
  size_t curNodeindex = 0;
  _SPC vector<GrapLineItem *> grapLinePool;
  //con::vector<GrapLineItem *>::Iter curLineIter;
  size_t curLineIndex = 0;

};

#endif