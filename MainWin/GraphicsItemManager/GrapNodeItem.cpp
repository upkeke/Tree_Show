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
QPointF operator*(const Pos &ps, const QPointF &pt) {
  return QPointF(ps.row * pt.x(), ps.col * pt.y());
}
QPointF operator*(const QPointF &pt, const Pos &ps) { return ps * pt; }
// QPointF gridToCoor(const Pos &ps,const QPointF &pt) {

//   return QPointF(x * 40, y * 60); }

} // namespace

GrapNodeItem::GrapNodeItem(const QPointF &pos, const QString &val,
                           NodeColor pix_c, QGraphicsItem *parent)
    : QGraphicsItem{parent}, val(val), color(pix_c)

{
  //:/m/img/pink.png
  pix.load(getPixFile(pix_c));
  toHeight();
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);

  setPos(pos);
}
GrapNodeItem::GrapNodeItem(Node<QString> *nodeptr, QGraphicsItem *parent)
    : QGraphicsItem{parent}, val(nodeptr->val), color(nodeptr->color) {
  pix.load(getPixFile(color));
  toHeight();
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);

  auto pos = *nodeptr * w_h;
  setPos(pos);
}

void GrapNodeItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  if (color == NodeColor::green || color == NodeColor::yellow) {
    painter->drawPixmap(boundingRect().topLeft(), pix); // 高度 30
  } else {
    if (color == NodeColor::pink) {
      painter->setBrush(Qt::red);
    } else {
      painter->setBrush(Qt::black);
    }
    painter->drawEllipse(QPointF(0, 0), 15, 15);
  }
  QFont font("微软雅黑", 15);
  painter->setPen(pen);
  painter->setFont(font);
  painter->drawText(boundingRect(), Qt::AlignCenter, val);
}

void GrapNodeItem::setVal(const QString &num) { val = num; }

QString GrapNodeItem::getVal() { return val; }

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
  color = ncolor;

  if (color == NodeColor::green || color == NodeColor::yellow) {
    pix.load(getPixFile(ncolor));
    pix = pix.scaledToHeight(30);
  }

  if (color == NodeColor::black)
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
void GrapNodeItem::reSet(const QPointF &pos, const QString &val,
                         NodeColor pix_c, QGraphicsItem *parent) {
  this->setPos(pos);
  this->val = val;
  this->color = pix_c;
  this->setParentItem(parent);
}
void GrapNodeItem::reSet(const Node<QString> &node) {

  this->setPos(node *);
  this->val = node.val;
  this->color = node.color;
  // this->setParentItem(parent);
}
void GrapNodeItem::toHeight(int order_h) { pix = pix.scaledToHeight(order_h); }