#include "GrapAnimItem.h"
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>

namespace {
QString OrderQStr(const EechOrder &order) {
  QString str;
  switch (order) {
  case EechOrder::先序:
    str = "先序";
    break;
  case EechOrder::中序:
    str = "中序";
    break;
  case EechOrder::后序:
    str = "后序";
    break;
  case EechOrder::层级:
    str = "层级";
    break;
  case EechOrder::选择:
    str = "选择";
    break;
  default:
    break;
  }
  return QString("%1遍历").arg(str);
}

} // namespace

UiForeachBtn::UiForeachBtn(EechOrder order) {
  setZValue(2);
  pix.load(":/GrapUi/img/遍历空-明.png");
  pix = pix.scaledToHeight(25);
  writeArea = QRectF(QPointF(0, 5), pix.size());
  this->order = order;
  int fontId = QFontDatabase::addApplicationFont(":/GrapUi/font/XiaoKeNa.ttf");
  QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
  font.setFamily(fontFamily);
  font.setPointSize(10);
}
void UiForeachBtn::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  // painter->drawPixmap(boundingRect().topLeft(), pix);
  painter->drawPixmap(0, 0, pix);
  painter->setFont(font);
  auto tl = writeArea.bottomLeft();

  painter->drawText(writeArea, Qt::AlignHCenter, OrderQStr(order));
}

QRectF UiForeachBtn::boundingRect() const {
  // return QRectF(QPointF(-pix.width() / 2.0, -pix.height() / 2.0),
  // pix.size());
  return QRectF(QPointF(), pix.size());
}
void UiForeachBtn::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

  if (event->button() == Qt::LeftButton) {
    qDebug() << "左键双击";
    // QPointF pos = this->mapToScene(boundingRect().bottomRight());
    emit ChildBtnPress(this->order);
  }
}
void UiForeachBtn::hide_() {
  this->hide();
  this->scene()->update();
}
/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/
UiForeachRootBtn::UiForeachRootBtn() {
  setZValue(2);
  // 下拉列表的根btn
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  // 遍历完整加明
  pix.load(":/GrapUi/img/遍历完整加暗.png");
  pix = pix.scaledToHeight(30);
  writeArea = QRectF(QPointF(20, 5), pix.size());
  this->order = EechOrder::选择;
  int fontId = QFontDatabase::addApplicationFont(":/GrapUi/font/XiaoKeNa.ttf");
  QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
  font.setFamily(fontFamily);
  font.setPointSize(15);
}
void UiForeachRootBtn::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

  if (event->button() == Qt::LeftButton) {
    qDebug() << "左键双击";
    // QPointF pos = this->mapToScene(boundingRect().bottomRight());
    emit RootBtnPress();
  }
}
bool UiForeachRootBtn::IsOpen() { return isOpen; }
void UiForeachRootBtn::set_IsOpen(bool flag) { this->isOpen = flag; }
void UiForeachRootBtn::set_order(EechOrder order) {
  this->order = order;
  this->scene()->update();
}

/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

namespace {

QVector<QPointF> getPoints(qreal r) {
  qreal rprime = r * sin(18 * M_PI / 180) / sin(126 * M_PI / 180);
  QPointF A{r * cos(18 * M_PI / 180), r * sin(18 * M_PI / 180)};
  QPointF B{r * cos(90 * M_PI / 180), r * sin(90 * M_PI / 180)};
  QPointF C{r * cos(162 * M_PI / 180), r * sin(162 * M_PI / 180)};
  QPointF D{r * cos(234 * M_PI / 180), r * sin(234 * M_PI / 180)};
  QPointF E{r * cos(306 * M_PI / 180), r * sin(306 * M_PI / 180)};
  QPointF F{rprime * cos(54 * M_PI / 180), rprime * sin(54 * M_PI / 180)};
  QPointF G{rprime * cos(126 * M_PI / 180), rprime * sin(126 * M_PI / 180)};
  QPointF H{rprime * cos(198 * M_PI / 180), rprime * sin(198 * M_PI / 180)};
  QPointF I{rprime * cos(270 * M_PI / 180), rprime * sin(272 * M_PI / 180)};
  QPointF J{rprime * cos(342 * M_PI / 180), rprime * sin(342 * M_PI / 180)};
  QVector<QPointF> points{B, F, A, J, E, I, D, H, C, G};
  return points;
}
_SPC vector<QPointF> getPentagonPoints(qreal radius) {
  _SPC vector<QPointF> points;
  for (int i = 0; i < 5; ++i) {
    qreal angle = 2 * M_PI / 5 * i;
    QPointF(QPointF(radius * cos(angle), radius * sin(angle)));
  }
  return points;
}
} // namespace

GrapMoveItem::GrapMoveItem(QPointF mPos, QGraphicsItem *parent)
    : QGraphicsItem(parent), wu(::getPoints(radius)) {
  setPos(mPos);
  setZValue(1);
}
void GrapMoveItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  painter->setBrush(Qt::red);
  painter->setPen(Qt::black);
  painter->drawPolygon(wu.data(), 10); // 画五角星
}
QRectF GrapMoveItem::boundingRect() const {
  return QRectF(QPointF(-radius, -radius), QSizeF(radius * 2, radius * 2));
}
QPainterPath GrapMoveItem::shape() const {
  QPainterPath path;
  path.addPolygon(wu);
  return path;
}
void GrapMoveItem::setRadius(int radius) {
  this->radius = radius;
  wu = getPoints(radius);
}
void GrapMoveItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  menu.addAction("Action 1");
  menu.addAction("Action 2");
  menu.exec(event->screenPos());
}
