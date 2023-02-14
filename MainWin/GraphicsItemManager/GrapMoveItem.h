
#pragma once
#ifndef __GRAPMOVEITEM__
#define __GRAPMOVEITEM__

#include "Grap_Bin.h"
#include <QGraphicsItem>
#include <config.h>

class GRAP_LIB_EXPORT GrapMoveItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  /**
   * @brief 注册pos属性
   *
   */
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  /**
   * @brief 注册旋转属性
   *
   */
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
public:
  GrapMoveItem() : QGraphicsItem(nullptr) { setZValue(3); }
  explicit GrapMoveItem(QPointF mPos, QGraphicsItem *parent = nullptr);
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
  // 讲解contextM
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
  /**
   * @brief 设置五角星的外接圆的半径
   *
   * @param radius
   */
  void setRadius(int radius);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

private:
  int radius = 20;
  QVector<QPointF> wu;
};

#endif
