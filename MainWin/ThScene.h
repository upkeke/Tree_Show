
#pragma once
#ifndef __THSCENE__
#define __THSCENE__

#include <QGraphicsScene>

class ThScene : public QGraphicsScene {
public:
  using QGraphicsScene::QGraphicsScene;
  ThScene(QObject *parent = nullptr);
  // TeScene() = default;

protected:
  //bool event(QEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  QPointF m_selectionStart;
  //框选框
  QGraphicsRectItem* m_selectionRectItem;
  //如果有图元被选中，那么鼠标左键移动不在出现框选
  bool isItemSelected = false;
};

#endif