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
GrapNodeItem::GrapNodeItem(NodePtr nodeptr, QGraphicsItem *parent)
    : QGraphicsItem{parent}, nodeptr(nodeptr) {
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  val = nodeptr->val;
  setZValue(0);
  setPos(nodeptr->Pos());
  initMenu();
}
void GrapNodeItem::initMenu() {
  menu = new QMenu();
  // 如果截断成功，当前节点会变成头节点
  auto a2 = menu->addAction("截断二叉树");
  connect(a2, &QAction::triggered, [this]() {
    if (nodeptr->isHead)
      return;
    NodePtr father = nullptr;
    bool isleft = false;
    for (auto line : lineArry) {
      auto [first, end] = line->getFrontEnd();
      GrapNodeItem *want = first;
      if (first == this) {
        want = end;
      }
      if (want->nodeptr->left == nodeptr) {
        line->hide();
        father = want->nodeptr;
        isleft = true;
        break;
      }
      if (want->nodeptr->right == nodeptr) {
        line->hide();
        father = want->nodeptr;
        break;
      }
    }
    if (father != nullptr) {
      qDebug() << "父节点是 " << QString::fromStdString(father->val);
      nodeptr->isHead = true;
      actionOnlyHead();
      // menu->addActions(const QList<QAction *> &actions)
      if (isleft) {
        father->left = nullptr;
      } else {
        father->right = nullptr;
      }
      this->scene()->update();
      emit truncateCurTree(this);
    }
  });
  auto a3 = menu->addAction("设置值");
  connect(a3, &QAction::triggered, [this]() { emit changeVal(nodeptr); });
  if (nodeptr->isHead) {
    actionOnlyHead();
  }
}
void GrapNodeItem::actionOnlyHead() {
  auto a1 = menu->addAction("更新位置到此处");
  connect(a1, &QAction::triggered, [this]() {
    auto offset = this->nodeptr->getOffsetByNowPos(this->pos());
    // this->nodeptr->color = NodeColor::gray;
    // this->scene()->update();
    emit updateTreePos(this->nodeptr, offset);
  });
  auto a2 = menu->addAction("变成主角");
  connect(a2, &QAction::triggered, [this]() { emit beStar(nodeptr); });
}
void GrapNodeItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->setBrush(nodeptr->color);
  painter->drawEllipse(QPointF(0, 0), radius, radius);

  painter->setPen(pen);

  painter->setFont(QFont("微软雅黑", 15));
  if (isShowDepth) {
    painter->drawText(boundingRect(), Qt::AlignCenter,
                      QString::number(nodeptr->col));
  } else {
#if HAS_QSTRING
    painter->drawText(boundingRect(), Qt::AlignCenter, nodeptr->val);
#else
    painter->drawText(boundingRect(), Qt::AlignCenter,
                      QString::fromStdString(nodeptr->val));
#endif
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

void GrapNodeItem::setVal(const _string &val) {
  this->val = val;
  scene()->update();
}

void GrapNodeItem::addLine(GrapLineItem *line) { lineArry.push_back(line); }

int GrapNodeItem::reMoveLines() {
  int re = lineArry.size();
  for (auto line : lineArry) {
    line->hide();
  }
  lineArry.clear();
  return re;
}

void GrapNodeItem::clearLines() { lineArry.clear(); }

QRectF GrapNodeItem::boundingRect() const {
  return QRectF(QPointF(-radius, -radius), QSizeF(radius * 2, radius * 2));
}
void GrapNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (isNew)
    if (this->isSelected()) {
      auto ls = collidingItems();
      if (ls.size() > 0) {
        emit andOther(ls[0]);
      }
    }
  nodeptr->setPos(pos());
  this->scene()->update();
  QGraphicsItem::mouseMoveEvent(event);
}

void GrapNodeItem::setBackColor(NodeColor ncolor) {
  nodeptr->color = ncolor;
  if (nodeptr->color == NodeColor::black)
    this->pen.setColor(Qt::white);
  else
    this->pen.setColor(Qt::black);
}

void GrapNodeItem::reSet(NodePtr nodeptr) { this->nodeptr = nodeptr; }
sbt::NodePtr GrapNodeItem::getNodePtr() { return this->nodeptr; }
void GrapNodeItem::setRadius(int radius) { this->radius = radius; }
void GrapNodeItem::setIsNew(bool flag) { this->isNew = flag; }
void GrapNodeItem::SetIsShowDepth(bool flag) { this->isShowDepth = flag; }
GrapNodeItem::~GrapNodeItem() { delete menu; }
