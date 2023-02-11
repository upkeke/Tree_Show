
#pragma once

#ifndef __GRAPUI_H1__
#define __GRAPUI_H1__

/*------------------------------------------------------------

这儿是各种控件，由图元构成
--------------------------------------------------------------
--------------------------------------------------------------
*/

#include "GrapUi_Bin.h"
#include <QFont>
#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <config.h>

enum class EechOrder { 先序, 中序, 后序, 层级, 选择 };
/**
 * @brief 这是遍历列表的子列表的按钮
 作用，点击后会开始五角星遍历动画，且修改列表根按钮的值
 *
 */
class GRAPUI_LIB_EXPORT UiForeachBtn : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  // UiForeachBtn(QGraphicsItem *parent = nullptr);
  UiForeachBtn(EechOrder order);
  //_ZN12UiForeachBtnC1EP13QGraphicsItem
  //__imp__ZN12UiForeachBtnC1E9EachOrderP13QGraphicsItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
public slots:
  void hide_();
signals:
  // 点击下拉框的下拉列表中的按钮，会把自己的EechOrder发送给根按钮，并收起
  // 展开下拉列表的按钮动画，再次点击收起
  void ChildBtnPress(EechOrder);

protected:
  UiForeachBtn() {}
  QPixmap pix;
  QFont font;
  // 文学书写区域
  QRectF writeArea;
  EechOrder order;
};

/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/

/**
 * @brief 这是遍历列表的根按钮
 作用是点击后生成子列表，再次点击则收起
 *
 */
class GRAPUI_LIB_EXPORT UiForeachRootBtn : public UiForeachBtn {
  Q_OBJECT
public:
  UiForeachRootBtn();
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  // 子列表是否被展开
  bool IsOpen();
  void set_IsOpen(bool flag);
  void set_order(EechOrder order);
signals:
  void RootBtnPress(QObject *);

private:
  // 子列表是否被展开
  bool isOpen = false;
};
/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/

/**
 * @brief 这个是生成按钮,清理按钮
 点击后会建立二叉树，再次点击会清空二叉树
 *
 */
class GRAPUI_LIB_EXPORT UiBuildClearBtn : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  UiBuildClearBtn();
  void func1() {

    this->parent();
    this->parentItem();
  }
};
#endif