#include "GrapNodeItem.h"
#include "GrapLineItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QString>

namespace {
QString getPixFile(const NodeColor &pix_c) {
  QString str;
  switch (pix_c) {
  case NodeColor::yellow:
    str = "yellow";
    break;
  case NodeColor::pink:
    str = "pink";
    break;
  case NodeColor::green:
    str = "green";
    break;
  default:
    break;
  }
  return QString(":/m/img/%1.jpg").arg(str);
}

// QPointF gridToCoor(const Pos &ps,const QPointF &pt) {

//   return QPointF(x * 40, y * 60); }

} // namespace

GrapNodeItem::GrapNodeItem(NodePtr nodeptr, QGraphicsItem *parent)
    : QGraphicsItem{parent}, nodeptr(nodeptr) {
  pix.load(getPixFile(nodeptr->color));
  toHeight();
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);

  setPos(QPointF(nodeptr->row, nodeptr->col));
}

void GrapNodeItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  if (nodeptr->color == NodeColor::green ||
      nodeptr->color == NodeColor::yellow) {
    painter->drawPixmap(boundingRect().topLeft(), pix); // 高度 30
  } else {
    if (nodeptr->color == NodeColor::pink) {
      painter->setBrush(Qt::red);
    } else {
      painter->setBrush(Qt::black);
    }
    painter->drawEllipse(QPointF(0, 0), 15, 15);
  }
  QFont font("微软雅黑", 15);
  painter->setPen(pen);
  painter->setFont(font);
  painter->drawText(boundingRect(), Qt::AlignCenter, nodeptr->val);
}

void GrapNodeItem::setVal(const QString &num) {
  nodeptr->val = num;
  nodeptr->val = num;
  scene()->update();
}

QString GrapNodeItem::getVal() { return nodeptr->val; }

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
  QSize tp = pix.size() / 2;
  QPointF lt(-tp.width(), -tp.height());
  return QRectF(lt, QSizeF(pix.width(), pix.height()));
  // return QRectF(QPointF(0,0), QSizeF(pix.width(), pix.height()));
}

void GrapNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseMoveEvent(event);
  if (this->isSelected())
    this->scene()->update();
}

void GrapNodeItem::setBackColor(NodeColor ncolor) {
  nodeptr->color = ncolor;

  if (nodeptr->color == NodeColor::green ||
      nodeptr->color == NodeColor::yellow) {
    pix.load(getPixFile(ncolor));
    pix = pix.scaledToHeight(30);
  }

  if (nodeptr->color == NodeColor::black)
    this->pen.setColor(Qt::white);
  else
    this->pen.setColor(Qt::black);
}

void GrapNodeItem::advance(int phase) {
  QGraphicsItem::advance(phase);
  return;
  if (phase == 0)
    return;
  // 每次向左移2 向下移1
  setPos(mapToScene(2, 1));
}
void GrapNodeItem::reSet(NodePtr nodeptr) {
  this->nodeptr = nodeptr;
  this->setPos(QPointF(nodeptr->row, nodeptr->col));
}
void GrapNodeItem::toHeight(int order_h) { pix = pix.scaledToHeight(order_h); }