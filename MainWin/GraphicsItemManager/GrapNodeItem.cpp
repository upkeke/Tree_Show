#include "GrapNodeItem.h"
#include "GrapLineItem.h"

#include <QDebug>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QString>

using namespace sbt;
GrapNodeItem::GrapNodeItem(NodePtr nodePtr, NodePtr headPtr,
                           QGraphicsItem *parent)
    : QGraphicsItem{parent}, nodePtr(nodePtr) {
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  val = nodePtr->val;
  setZValue(0);
  setPos(nodePtr->Pos());
  initMenu();
  setHeadPtr(headPtr);
}
void GrapNodeItem::initMenu() {
  menu = new QMenu();

  auto a0 = menu->addAction("变成主角");
  actions[0] = a0;
  connect(a0, &QAction::triggered, [this]() { emit beStar(nodePtr); });
  // 如果截断成功，当前节点会变成头节点
  auto a1 = menu->addAction("截断二叉树");
  actions[1] = a1;
  connect(a1, &QAction::triggered, [this]() { emit truncateCurTree(this); });
  auto a2 = menu->addAction("设置值");
  actions[2] = a2;
  connect(a2, &QAction::triggered, [this]() { emit changeVal(nodePtr); });
  auto a3 = menu->addAction("删除");
  actions[3] = a3;
  connect(a3, &QAction::triggered, [this]() { emit deleteNodeItem(this); });
  menu->addActions(actions);
}

void GrapNodeItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->setBrush(nodePtr->color);
  if (isSelected()) {
    pen.setStyle(Qt::DotLine);
  } else {
    pen.setStyle(Qt::SolidLine);
  }
  painter->setPen(pen);
  painter->drawEllipse(QPointF(0, 0), radius, radius);

  painter->setFont(QFont("微软雅黑", 15));
  if (isShowDepth) {
    painter->drawText(boundingRect(), Qt::AlignCenter,
                      QString::number(nodePtr->col));
  } else {
    painter->drawText(boundingRect(), Qt::AlignCenter, nodePtr->val);
  }
}
QPainterPath GrapNodeItem::shape() const {
  QPainterPath path;
  path.addEllipse(QPointF{0, 0}, radius, radius);
  return path;
}
void GrapNodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  menu->exec(event->screenPos());
}

void GrapNodeItem::setVal(const QString &val) {
  this->val = val;
  scene()->update();
}

void GrapNodeItem::setChildLines(GrapLineItem *line, bool isLeft) {
  if (isLeft)
    lineChild[0] = line;
  else
    lineChild[1] = line;
}

void GrapNodeItem::setFatherItem(GrapNodeItem *father) { fatherItem = father; }
GrapNodeItem *GrapNodeItem::getFatherItem() { return fatherItem; }
std::array<GrapLineItem *, 2> GrapNodeItem::reMoveLines() {
  auto re = lineChild;
  for (auto &line : lineChild) {
    line = nullptr;
  }
  return re;
}
GrapLineItem *GrapNodeItem::rmoveLine(bool isLeft) {
  GrapLineItem *re = nullptr;
  if (isLeft) {
    re = lineChild[0];
    lineChild[0] = nullptr;
  } else {
    re = lineChild[1];
    lineChild[1] = nullptr;
  }
  return re;
}
// void GrapNodeItem::hideLines() { lineChild.clear(); }

QRectF GrapNodeItem::boundingRect() const {
  return QRectF(QPointF(-radius, -radius), QSizeF(radius * 2, radius * 2));
}
void GrapNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseMoveEvent(event);
  if (this->isSelected()) {
    if (isHeadItem()) {
      auto ls = collidingItems();
      if (ls.size() > 0) {
        auto other = qgraphicsitem_cast<GrapNodeItem *>(ls[0]);
        if (other != nullptr && other->headPtr != headPtr)
          emit mergeToOther(other, this);
      }
    }
    nodePtr->setPos(pos());
    this->scene()->update();
  }
}

void GrapNodeItem::setBackColor(NodeColor ncolor) {
  nodePtr->color = ncolor;
  if (nodePtr->color == NodeColor::black)
    this->pen.setColor(Qt::white);
  else
    this->pen.setColor(Qt::black);
}

// void GrapNodeItem::reSet(NodePtr nodePtr) { this->nodePtr = nodePtr; }
sbt::NodePtr GrapNodeItem::getNodePtr() { return this->nodePtr; }
void GrapNodeItem::setRadius(int radius) { this->radius = radius; }
// void GrapNodeItem::setIsNew(bool flag) { this->isNew = flag; }
void GrapNodeItem::SetIsShowDepth(bool flag) { this->isShowDepth = flag; }
GrapNodeItem::~GrapNodeItem() { delete menu; }
void GrapNodeItem::setHeadPtr(sbt::NodePtr head) {
  this->headPtr = head;
  auto isHead = isHeadItem();
  actions[0]->setVisible(isHead);
  actions[1]->setVisible(!isHead);
  if (isHead)
    nodePtr->color = NodeColor::magenta;
  else
    nodePtr->color = NodeColor::yellow;
}
sbt::NodePtr GrapNodeItem::getHeadPtr() { return headPtr; }
void GrapNodeItem::reSet(sbt::NodePtr nodeptr, sbt::NodePtr headPtr) {
  this->nodePtr = nodeptr;
  setHeadPtr(headPtr);
}
